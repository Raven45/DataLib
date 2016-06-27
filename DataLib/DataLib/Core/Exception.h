/************************************************************************
Copyright 2016 Aaron Burns

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
************************************************************************/

#ifndef DATALIB_EXCEPTION
#define DATALIB_EXCEPTION

namespace DataLib {

	static const char* EXCEPTION_LOCKED				= "DataLib::0x0001: Object is write protected!";
	static const char* EXCEPTION_STACK_OVERFLOW		= "DataLib::0x0002: Call stack has overflown!";
	
	class Exception {
		
		friend class Object;
		//friend class List;
		
	public:
		const char* GetError();
		
	//private:
		Exception();
		
		const char* Error;
		
	};
}

#endif