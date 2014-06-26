goto start

:: Option 		Description
:: -1			Generate SOAP 1.1 bindings
:: -2			Generate SOAP 1.2 bindings
:: -0			Remove SOAP bindings, use plain REST
:: -C			Generate client-side code only
:: -S			Generate server-side code only
:: -T			Generate server auto-test code
:: -L			Do not generate soapClientLib/soapServerLib
:: -a			Use SOAPAction with WS-Addressing to invoke server-side operations
:: -A			Require SOAPAction to invoke server-side operations
:: -b			serialize byte arrays char[N] as string
:: -c			Generate pure C code
:: -d < path > 	Save sources in directory specified by < path >
:: -e			Generate SOAP RPC encoding style bindings
:: -f N			File split of N XML serializer implementations per file
:: -h			Print a brief usage message
:: -i			Generate service proxies and objects inherited from soap struct
:: -j			Generate C++ service proxies and objects that can share a soap struct
:: -I < path > 	Use < path > for #import (paths separated with ':' or ';' for windows)
:: -k			generate data structure walkers (experimental)
:: -l			Generate linkable modules (experimental)
:: -m			Generate Matlabtm code for MEX compiler
:: -n			When used with -p, enables multi-client and multi-server builds:
:: 				Sets compiler option WITH_NONAMESPACES, see Section 9.11
:: 				Saves the namespace mapping table with name < name > _namespaces instead of namespaces
:: 				Renames soap_serve() into < name > _serve() and soap_destroy() into < name > _destroy()
:: -p < name > 	Save sources with file name prefix < name > instead of "soap"
:: -q < name > 	Use name for the C++ namespace of all declarations
:: -s			Generates deserialization code with strict XML validation checks
:: -t			Generates code to send typed messages (with the xsi:type attribute)
:: -u			uncomment comments in WSDL/schema output by suppressing XML comments
:: -v			Display version info
:: -w			Do not generate WSDL and schema files
:: -x			Do not generate sample XML message files
:: -y			include C/C++ type access information in sample XML messages
:: -z1			generate deprecated old-style C++ service proxies and objects 

:: example
::		soapcpp2.exe -i -d ../gen -prd rdms.h


::		产生server端代码
::		soapcpp2.exe -i -S -d ../genc rdms.h
::		产生客户端端代码
::		soapcpp2.exe -i -C -d ../genc rdms.h

::		产生server端代码/产生客户端端代码
::		soapcpp2.exe -i -d ../gen rdms.h

::		产生server端代码/产生客户端端代码,不包含继承自soap的类
::		soapcpp2.exe -d ../gen rdms.h
:start

soapcpp2.exe -s -d ../gen rdms.h
