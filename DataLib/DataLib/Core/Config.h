/***********************************************************************
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
***********************************************************************/

#ifdef _Win32
	#define WindowsLegacy
#endif

#ifdef _Win64
	#define Windows
#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
	#define Unix
#endif

/***********************************************************************
Unix compatibility for null pointers. 
***********************************************************************/
#ifdef Unix
	#define nullptr 0
#endif
