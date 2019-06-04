cmake_minimum_required(VERSION 3.0)

project(libxml2)

set(CMAKE_C_STANDARD 99)

# Set versions
set(MAJOR_VERSION 2)
set(MINOR_VERSION 9)
set(MICRO_VERSION 9)
set(MICRO_VERSION_SUFFIX)
set(
	VERSION
	${MAJOR_VERSION}.${MINOR_VERSION}.${MICRO_VERSION}${MICRO_VERSION_SUFFIX}
)
set(LIBXML_VERSION ${VERSION})
math(
	EXPR LIBXML_VERSION_NUMBER
	"${MAJOR_VERSION} * 10000 + ${MINOR_VERSION} * 100 + ${MICRO_VERSION}"
)
set(LIBXML_VERSION_EXTRA)

# Configurations
set(WITH_TRIO 0)
set(WITH_THREADS 0)
set(WITH_THREAD_ALLOC 0)
set(WITH_TREE 1)
set(WITH_OUTPUT 1)
set(WITH_PUSH 1)
set(WITH_READER 1)
set(WITH_PATTERN 0)
set(WITH_WRITER 1)
set(WITH_SAX1 1)
set(WITH_FTP 0)
set(WITH_HTTP 0)
set(WITH_VALID 1)
set(WITH_HTML 0)
set(WITH_LEGACY 0)
set(WITH_C14N 0)
set(WITH_CATALOG 0)
set(WITH_DOCB 0)
set(WITH_XPATH 0)
set(WITH_XPTR 0)
set(WITH_XINCLUDE 0)
set(WITH_ICONV 0)
set(WITH_ICU 0)
set(WITH_ISO8859X 0)
set(WITH_DEBUG 0)
set(WITH_MEM_DEBUG 0)
set(WITH_RUN_DEBUG 0)
set(WITH_REGEXPS 1)
set(WITH_SCHEMAS 0)
set(WITH_SCHEMATRON 0)
set(WITH_MODULES 0)
set(WITH_ZLIB 0)
set(WITH_LZMA 0)

# Generate xmlversion.h
configure_file(
	include/libxml/xmlversion.h.in
	"${CMAKE_CURRENT_BINARY_DIR}/libxml/xmlversion.h"
	@ONLY
)

# Check headers
include(CcChecks)
cc_check_headers(
	arpa/inet.h
	arpa/nameser.h
	ctype.h
	dirent.h
	dl.h
	dlfcn.h
	errno.h
	fcntl.h
	float.h
	inttypes.h
	limits.h
	malloc.h
	math.h
	netdb.h
	netinet/in.h
	poll.h
	resolv.h
	signal.h
	stdint.h
	stdlib.h
	string.h
	strings.h
	sys/mman.h
	sys/select.h
	sys/socket.h
	sys/stat.h
	sys/time.h
	sys/timeb.h
	sys/types.h
	time.h
	unistd.h
    stdarg.h
)

include(CheckCSourceCompiles)

# Check va_copy
check_c_source_compiles(
    "
        #include <stdarg.h>
        va_list ap1, ap2;
        int main() { va_copy(ap1, ap2); }
    "
    HAVE_VA_COPY
)
if(HAVE_VA_COPY)
    add_definitions(-DHAVE_VA_COPY)
endif()
check_c_source_compiles(
    "
        #include <stdarg.h>
        va_list ap1, ap2;
        int main() { __va_copy(ap1, ap2); }
    "
    HAVE___VA_COPY
)
if(HAVE___VA_COPY)
    add_definitions(-DHAVE___VA_COPY)
endif()

# Check whether va_list is array
check_c_source_compiles(
    "
        #include <stdarg.h>
        void a(va_list *ap) {}
        int main() {
            va_list ap1, ap2;
            a(&ap1);
            ap2 = (va_list) ap1;
        }
    "
    VA_LIST_IS_ARRAY
)
if(VA_LIST_IS_ARRAY)
    add_definitions(-DVA_LIST_IS_ARRAY)
endif()

# Check functions
cc_check_funcs(
	fprintf
	ftime
	gettimeofday
	isascii
	localtime
	mmap
	munmap
	printf
	putenv
	rand
	rand_r
	signal
	snprintf
	sprintf
	srand
	sscanf
	stat
	strftime
	time
	vfprintf
	vsnprintf
	vsprintf
)

# Sources
set(
    XML2_SOURCES
    SAX.c
	entities.c
	encoding.c
	error.c
	parserInternals.c
	parser.c
	tree.c
	hash.c
	list.c
	xmlIO.c
	xmlmemory.c
	uri.c
	valid.c
	xlink.c
	HTMLparser.c
	HTMLtree.c
	debugXML.c
	xpath.c
    xpointer.c
	xinclude.c
	nanohttp.c
	nanoftp.c
	catalog.c
	globals.c
	threads.c
	c14n.c
	xmlstring.c
	buf.c
	xmlregexp.c
	xmlschemas.c
	xmlschemastypes.c
	xmlunicode.c
	xmlreader.c
	relaxng.c
	dict.c
	SAX2.c
	xmlwriter.c
	legacy.c
	chvalid.c
	pattern.c
	xmlsave.c
	xmlmodule.c
	schematron.c
	xzlib.c
)

include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}
)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_library(xml2 ${XML2_SOURCES})
