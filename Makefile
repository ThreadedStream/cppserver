STANDARD = c++17
LIBPATH=/usr/lib/x86_64-linux-gnu	
LINUX_THREAD=-pthread
BOOST_THREAD=-lboost_thread

OUTPUT=cppserver
build_gcc:
	g++ -O2 -std=$(STANDARD)  -o $(OUTPUT) CppServer/servers/http_server/http_server.cpp \
	CppServer/servers/http_server/connection.cpp CppServer/core/app.cpp CppServer/core/dbconn.cpp \
  CppServer/servers/http_server/response.cpp CppServer/servers/http_server/request.cpp \
	CppServer/math_unit.cpp CppServer/main.cpp -L$(LIBPATH) $(BOOST_THREAD) $(LINUX_THREAD) 

# Clang will be added soon (not sure, though)