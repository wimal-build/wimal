.. _apple_codesign_remote_signing_design:

======================================================
Remote Code Signing Design and Security Considerations
======================================================

Design Goals and Constraints
============================

The design of remote signing is influenced with the following primary goals in
mind:

* The initiating machine MUST NOT have direct access to the private signing
  key. Ever. The private key (or ability to create signatures with it) is only
  ever in possession of the signer.
* The private key cannot be used without the signer's knowledge (and optional
  consent to each use).
* The initiating machine must be able to run remotely / non-interactively.

We also imposed the following constraints when considering designs:

* The initiating machine is partially trusted. We assume that if you trust the
  initiating machine to invoke a signing operation then you trust that machine
  to e.g. not lie about the signing requests it subsequently presents to the
  signer.
* We should place minimal trust in any 3rd party servers or machines. Assume
  all 3rd parties are malicious and will attempt to coerce signers into signing
  arbitrary content.
* 3rd party servers should have access to as little information about signing
  activity as possible. e.g. 3rd party servers should not be able to observe
  the messages that are signed, the produced signatures, or the certificates
  used to sign. They may observe details that leak through side channels, such
  as the number of messages exchanged and the sizes of encrypted ciphertexts.
* We assume the existence of an out-of-band side-channel for 2 peers to exchange
  information at signing time. This means we require some synchronous activity
  by the signer in order to fulfill signing requests. (The signer isn't just
  running an always-running server that responds to signing requests.)

Threat Models
=============

The following threat models dictate some design choices:

* A malicious brokering server or man-in-the-middle could coerce the signer into
  signing unwanted content.
* A malicious 3rd party could disrupt signing operations by sending garbage
  messages to the brokering server, either in general or directed at established
  sessions. i.e. DoS against the server.
* A malicious brokering server or man-in-the-middle could fulfill signature
  requests using the *wrong* certificate.

If signing sessions were conducted without any prior knowledge of the peer,
neither peer would be able to trust or authenticate the other. You could
securely exchange end-to-end encrypted messages with a peer. But the *initiator*
wouldn't be able to answer the question *is this signed by who I want it to be
signed by*. And more importantly, the *signer* wouldn't be able to answer
*do I trust the initiator to send me content that I want to sign*.

You can't establish a trust relationship without a trust anchor. **So in order
to establish trust we require that peers share pre-existing knowledge of the
other before signing operations.** The exact mechanism can vary. But *some*
pre-existing knowledge needs to be conveyed to the other peer in order to serve
as a trust anchor.

Since all designs rule out the possibility of the private key being directly
accessed or used by the *initiator*, the next best attack vector is tricking
the *signer* into signing untrusted/malicious content.

The easiest way to conduct this attack is for a malicious server or
man-in-the-middle to intercept communications and/or issue a malicious signing
request. There are a few mitigations for this.

First, *signers* must have presence in order to create signatures. When signers
go offline, they can't produce signatures. So attacks against signers must occur
when the signer is online.

Second, we employ end-to-end encryption of peer-to-peer messages using
ephemeral encryption keys unique to the session and logically derived from a
pre-existing trust anchor. A malicious 3rd party would need access to data
never transmitted in plaintext through the server in order to decrypt messages
or issue fake/malicious messages.

Security Analysis in the Bigger Picture
=======================================

When considering the overall security of remote code signing, we have to
consider the broader ecosystem in which it exists.

Without remote code signing, the following are all commonly true:

* Signing keys are copied to multiple machines to make it easier to access
  them.
* Signing keys are made available as secrets on CI workers.
* Access to perform operations on the signing key is always on. e.g.
  anybody who can talk to the HSM can create a signature.
* Security conscious people (those who want to minimize risk for private
  keys) need to impose a more complicated release pipeline - one that
  typically entails copying assets to a separate machine, signing them,
  then copying elsewhere. These steps are often tedious and effectively
  constitute a barrier to good security hygiene.

There are general principles of private key management:

* You should have as few copies of the private key as possible. Ideally 1.
* Keys should be as short lived as possible or access to them should be
  limited in time duration.

Traditional solutions to code signing violate these principles because
there's not an easy-to-use / viable alternative. So in the absence of
remote code signing, commonly practiced code signing key management is
generally not great.

We believe that our design of remote code signing is intrinsically more
secure than what is commonly practiced because:

* The signer in possession of the private key must be present. There is
  no unlimited access to the private key outside an active signing session.
* You can have exactly 1 copy of the private key without compromising on
  usability. The urge to make copies to streamline CI/CD is largely mitigated
  via an easy-to-use remote signing UI.

In addition, the design and implementation of the relay server further
bolsters security by:

* Purging sessions after a maximum time to live (measured in minutes).
* Refusing to allow N>2 peers from sending messages to a session.
* Requiring active presence for message exchange. The server doesn't store
  a copy of relayed signing messages so there isn't a potential for someone
  to deposit a malicious message for later retrieval.

And these security properties are delivered without even factoring in
end-to-end message encryption! The end-to-end encryption is effectively
protections against a malicious server or man-in-the-middle. These are
arguably necessary protections - especially when using a server hosted by
an (untrusted) 3rd party. But for scenarios where you run your own server
and you trust the network, end-to-end encryption isn't buying you much beyond
what signer presence requirements and server design already deliver.

Default Remote Code Signing Server
==================================

By default, this project uses the remote code signing server at
``wss://ws.codesign.gregoryszorc.com/``.

This service is operated by the maintainer of this project and is provided
for free for use by the community. However, there is no formal or legal
agreement around the availability of its service or its operation.

The service is hosted on AWS and uses API Gateway + Lambda + DynamoDB
and should be highly reliable, as these services rarely experience outages.

The :ref:`apple_codesign_remote_signing_protocol` and implementation of the
server have been purposefully designed to be respectful of privacy of its
users.

Meaningful messages between clients are end-to-end encrypted and the server
is unable to determine the contents of those messages. The server only has
access to protocol-level details, such as which APIs are being invoked and
the sizes of the payloads.

The server does have access to client IPs and any additional metadata
in HTTP requests and websocket frames. However, IPs or other identifying
information is not read by our custom code powering the websocket server or
retained in any logs to the best of our knowledge. (We believe user data
to be toxic and don't want anything to do with it.)

Some metrics to monitor the health of the service and help prevent abuse
are recorded. These include the counts of different API invocations and
the sizes of message payloads.

The code powering the server and the Terraform for deploying it on AWS
are open source and available to audit. See
:ref:`apple_codesign_remote_signing_running_your_own_server` for details.
Of course, there's no way to prove that ``ws.codesign.gregoryszorc.com``
is running the same configuration as the provided open source code. You
*just* have to trust that the maintainer of this project values the privacy
of his users.

.. _apple_codesign_remote_signing_running_your_own_server:

Running Your Own Server
=======================

If you are unable or unwilling to use the default remote signing server
operated by the maintainer of this project, it is possible to deploy your
own server instance.

The source code for the server and a Terraform module for deploying it into
AWS are available in this repository in the
``terraform-modules/remote-code-signing`` directory. The canonical location
is https://github.com/indygreg/apple-platform-rs/tree/main/terraform-modules/remote-code-signing.

See its README for instructions on how to use. Once deployed at a different
hostname, you'll need to provide the ``--remote-signing-url`` argument to
relevant commands to override the default signing server URL.
