// $Id$
// Copyright (c) SharpSvn Project 2007 
// The Sourcecode of this project is available under the Apache 2.0 license
// Please read the SharpSvnLicense.txt file for more details

#include "stdafx.h"

#pragma warning(disable: 4635)
#pragma warning(disable: 4634) // XML document comment: cannot be applied:  Discarding XML document comment for invalid target.

#include <apr-1/apr_version.h>
#include <apr-1/apu_version.h>
#if (APU_HAVE_APR_ICONV != 0)
#include <apr-1/api_version.h>
#endif
#include <svn_version.h>
#include <serf/serf.h>
#include <openssl/opensslv.h>
#include <neon/neon_version.h>	// Generated by our import script as we can't use config.h
#include <db.h>
#define STRUCT_IOVEC_DEFINED // Kill compile error

#include <sasl/sasl.h>	// Generated by our import script as we can't use config.h

using namespace System;
using namespace System::Reflection;
using namespace System::Resources;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

#define SERF_VERSION APR_STRINGIFY(SERF_MAJOR_VERSION) \
                           "." APR_STRINGIFY(SERF_MINOR_VERSION) \
                           "." APR_STRINGIFY(SERF_PATCH_VERSION)

#define BDB_VERSION APR_STRINGIFY(DB_VERSION_MAJOR) "." APR_STRINGIFY(DB_VERSION_MINOR) "." APR_STRINGIFY(DB_VERSION_PATCH)

#define SASL_VERSION APR_STRINGIFY(SASL_VERSION_MAJOR) "." APR_STRINGIFY(SASL_VERSION_MINOR) "." APR_STRINGIFY(SASL_VERSION_STEP)
//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute("SharpSvn - Subversion for .Net 2.0")];
[assembly:AssemblyDescriptionAttribute("SharpSvn (Compiled statically with subversion " SVN_VER_NUMBER
									   ", apr " APR_VERSION_STRING
									   ", apr-util " APU_VERSION_STRING
#if (APU_HAVE_APR_ICONV != 0)
									   ", apr-iconv " API_VERSION_STRING
#endif
									   ", neon " NEON_VERSION
									   ", serf " SERF_VERSION
									   " and " OPENSSL_VERSION_TEXT
									   " and dynamically linked to Berkeley DB" BDB_VERSION 
									   " and Cyrus Sasl " SASL_VERSION ")")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("SharpSvn Project")];
[assembly:AssemblyProductAttribute("SharpSvn")];
[assembly:AssemblyCopyrightAttribute("Copyright � SharpSvn Project 2007")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version
//      Build Number
//      Revision
//
// You can specify all the value or you can default the Revision and Build Numbers
// by using the '*' as shown below:

[assembly:AssemblyVersionAttribute("1.5.0.3")];
[assembly:NeutralResourcesLanguageAttribute("en")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];

[assembly:RuntimeCompatibility(WrapNonExceptionThrows = true)];
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "User32.lib")

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#pragma comment(lib, "libsvn_client-1.lib")
#pragma comment(lib, "libsvn_delta-1.lib")
#pragma comment(lib, "libsvn_diff-1.lib")
#pragma comment(lib, "libsvn_fs-1.lib")
#pragma comment(lib, "libsvn_fs_base-1.lib")
#pragma comment(lib, "libsvn_fs_fs-1.lib")
#if (SVN_VER_MAJOR > 1 || SVN_VER_MINOR >= 5)
#pragma comment(lib, "libsvn_fs_util-1.lib")
#pragma comment(lib, "sqlite3.lib")
#endif

#pragma comment(lib, "libsvn_ra-1.lib")
#if (SVN_VER_MAJOR > 1 || SVN_VER_MINOR >= 5)
#pragma comment(lib, "libsvn_ra_neon-1.lib")
#pragma comment(lib, "libsvn_ra_serf-1.lib")
#pragma comment(lib, "libsasl.lib")
#else
#pragma comment(lib, "libsvn_ra_dav-1.lib")
#endif
#pragma comment(lib, "libsvn_ra_local-1.lib")
#pragma comment(lib, "libsvn_ra_svn-1.lib")
#pragma comment(lib, "libsvn_repos-1.lib")
#pragma comment(lib, "libsvn_subr-1.lib")
#pragma comment(lib, "libsvn_wc-1.lib")
#pragma comment(lib, "xml.lib")
#pragma comment(lib, "libneon.lib")
#if (SVN_VER_MAJOR > 1 || SVN_VER_MINOR >= 5)
#pragma comment(lib, "serf.lib")
#endif
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libdb45.lib")

#if (APR_MAJOR_VERSION == 0) && (APR_MINOR_VERSION == 9)
#  pragma comment(lib, "apr.lib")
#  pragma comment(lib, "aprutil.lib")
#  if (APU_HAVE_APR_ICONV != 0)
#    pragma comment(lib, "apriconv.lib")
#  endif
#elif (APR_MAJOR_VERSION == 1)
#pragma comment(lib, "apr-1.lib")
#pragma comment(lib, "aprutil-1.lib")
#  if (APU_HAVE_APR_ICONV != 0)
#    pragma comment(lib, "apriconv-1.lib")
#  endif
#else
#error Only apr 0.9.* and 1.* are supported at this time
#endif
