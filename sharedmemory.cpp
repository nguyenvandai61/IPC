#include "SharedMemory.h"

SharedMemory::SharedMemory()
{

}
SharedMemory::SharedMemory(const char* name, bool createMode, size_t size=1024)
{
	init(name, createMode, size);
}

SharedMemory::~SharedMemory()
{
	
}

void* SharedMemory::read()
{
	void* pt = open(1024);
	char* pchar = (char*)pt;
	// cout << "Doc du lieu kieu text\n";
	// for (int i = 0; i < 10; i++) {
	// 	printf("Data[%d] = %3d\n", i, pchar[i]);
	// }

	// cout << "Doc du lieu kieu double\n";
	// for (int i = 0; i < 10; i++) {
	// 	printf("Data[%d] = %lf\n", i, *((double*)pt+i));
	// }
	return pchar;
}

bool SharedMemory::write(const char* data)
{
	if (data == nullptr) 
		return false;
	void* p = open(1024);

	cout << "San sang ghi du lieu \n";
	CopyMemory((PVOID)p, data, strlen(data)* sizeof(char));
	// for (int i = 0; i < 8; i++) {
	// 	cout << "Data sau khi ghi vao" << *((PVOID*)p+i) << "\n ";
	// }
	return true;
}

bool SharedMemory::write(double* data)
{

	if (data == nullptr)
		return false;

	p = open(1024);
	cout << "SM San sang ghi du lieu \n";
	//const char* s = data;
	cout << "SM Noidung ghi: " << data;
	CopyMemory((PVOID)p, data, sizeof(double));
	for (int i = 0; i < 8; i++) {
		cout << "SM Data an sau khi ghi vao:" << *((double*)(PVOID*)p+i) << "\n ";
	}
	return true;
}





void* SharedMemory::create(size_t bufsize)
{
	cout << "SM Creating a SharedMemory\n";
	HANDLE pageFile = INVALID_HANDLE_VALUE;
	LPSECURITY_ATTRIBUTES securAttrs = NULL;
	DWORD access = PAGE_READWRITE;
	DWORD sizeHigh = NULL;
	DWORD sizeLow = bufsize;
	mappingHandle = CreateFileMappingA(pageFile, securAttrs, access, sizeHigh, sizeLow, name.c_str());
	if (mappingHandle == NULL) {
		perror("Error");
		return 0;
	}
	p = MapViewOfFile(mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, bufsize);
	if (!p) {
		perror("err");
		return 0;
	}
	cout << "Success in Creating\n";
	return p;
}

void* SharedMemory::open(size_t bufsize) {

	cout << "Opening a SharedMemory\n";
	DWORD access = FILE_MAP_ALL_ACCESS;
	BOOL inherit = FALSE;
	mappingHandle = OpenFileMapping(access, inherit, name.c_str());

	if (mappingHandle == NULL || mappingHandle == INVALID_HANDLE_VALUE)
	{
		perror("OpenFileMapping failed, ");
		return 0;
	}
	p = MapViewOfFile(mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, bufsize);
	if (!p)
	{
		perror("MapViewOfFile");
		return 0;
	}
	cout << "Success in Opening SharedMemory\n";
	return p;
}

void SharedMemory::reset()
{

	cout << "Reset a SharedMemory\n";
	/*for (int i = 0; i < 8; i++) {
		cout << "Data sau reset" << *((PVOID*)p + i) << "\n ";
	}*/
	if (p)
		UnmapViewOfFile(p);
	if (mappingHandle > 0) CloseHandle(mappingHandle);
	
}
void SharedMemory::close()
{

	cout << "Closing a SharedMemory\n";
	if (p)
		UnmapViewOfFile(p);
	if (mappingHandle > 0) CloseHandle(mappingHandle);
}
