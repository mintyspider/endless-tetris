GLUT 3.7.6-6.mp for MSVC

This package contains an MSVC header, import library, and DLL built using
Microsoft’s Visual Studio 2008. The package is built from the source code from
Nate Robins’ site (http://www.xmission.com/~nate/glut.html), and is binary
compatible with the DLL available from there.

The “glut.h” header has an additional preprocessor definition to allow it to
work with MinGW, and the DLL has had a version resource added to it so the
version information and copyright is viewable using Windows Explorer. Otherwise,
the package is identical to the original.

It should be noted that this package comes with very little support, and is
provided only for reasons of backwards compatibility. Unless you have some
specific reason to use GLUT for Win32, then I would recommend using freeglut
(http://freeglut.sourceforge.net/) instead. It’s a much more up to date GLUT
package which is actively maintained, and switching from GLUT for Win32 to
freeglut should be a matter of a simple recompile.


Installation

Create a folder on your PC which is readable by all users, for example
“C:\Program Files\Common Files\MSVC\GLUT\” on a typical Windows system. Copy the
“lib\” and “include\” folders from this zip archive to that location.

The GLUT for Win32 DLL should either be placed in the same folder as your
application, or can be installed in a system-wide folder which appears in your
%PATH% environment variable. On a 32 bit Windows system this is typically
“C:\Windows\System32\”, and on a 64 bit Windows system this is typically
“C:\Windows\SysWOW64\”.


Compiling Applications

To create a GLUT for Win32 application, create a new Win32 C++ project in MSVC.
From the “Win32 Application Wizard”, choose a “Windows application”, check the
“Empty project” box, and submit.

You’ll now need to configure the compiler and linker settings. Open up the
project properties, and select “All Configurations” (this is necessary to ensure
our changes are applied for both debug and release builds). Open up the
“general” section under “C/C++”, and configure the “include\” folder you created
above as an “Additional Include Directory”. If you have more than one GLUT
package which contains a “glut.h” file, it’s important to ensure that the GLUT
for Win32 include folder appears above all other GLUT include folders.

Now open up the “general” section under “Linker”, and configure the “lib\”
folder you created above as an “Additional Library Directory”. A GLUT for Win32
application depends on the import libraries “glut32.lib” and “opengl32.lib”,
which can be configured under the “Input” section, however it shouldn’t be
necessary to explicitly state these dependencies, since the GLUT header handles
this for you. Now open the “Advanced” section, and enter “mainCRTStartup” as the
“Entry Point” for your application. This is necessary because GLUT applications
use “main” as the application entry point, not “WinMain”—without it you’ll get
an undefined reference when you try to link your application.

That’s all of your project properties configured, so you can now add source
files to your project and build the application.

Don’t forget to either include the GLUT DLL when distributing applications, or
provide your users with some method of obtaining it if they don’t already have
it!


Changelog

2010–01–22: Release 3.7.6-6.mp

  • Rebuilt the DLL with a minimum OS version of 4.00, so it can work under
    Windows NT 4 and Windows 98. Previously it required at least Windows 2000.

2009–12–22: Release 3.7.6-5.mp

  • Updated documentation to take into account the fact that 32 bit DLLs should
    be placed in the “SysWOW64” folder on 64 bit Windows versions, rather than
    “System32”.

2009–09–27: Release 3.7.6-4.mp

  • Included a Windows DLL built with MSVC, rather than relying on Nate Robins’
    DLL which is statically linked against an old version of Microsoft’s C
    runtime.

  • Added a version resource to the DLL, allowing the version information and
    copyright to be viewed using Windows Explorer.


Martin Payne
2010–01–22

http://www.transmissionzero.co.uk/
