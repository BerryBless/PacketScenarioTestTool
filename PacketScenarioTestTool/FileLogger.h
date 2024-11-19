#pragma once
//-------------------------------------------------------------------------------------------------------------
// 로그 파일 만드는 클래스
//-------------------------------------------------------------------------------------------------------------
#include <concurrent_queue.h>
#include "TextFile.h"
// 멀티스레드에서 여러곳에서 접근 가능하기 떄문에
// 큐잉후 스레드에서 해소 
class FileLogger
{
public:
	FileLogger();
	~FileLogger();
	static FileLogger& Instance()
	{
		static FileLogger instance;
		return instance;
	}
private:
	//싱글톤 사용시 혹시모를 복제 차단
	FileLogger(const FileLogger&) = delete;
	FileLogger& operator=(const FileLogger&) = delete;
	FileLogger(FileLogger&&) = delete;
	FileLogger& operator=(FileLogger&&) = delete;
public:
	// Thread
	void ThreadStart();
	void ThreadLoop();
	void ThreadStop();

	// File
	bool MakeFile(const CTime& curTime);
	void Init(std::wstring_view file_name_prefix, std::wstring_view file_extension = L"txt");
	void Write(std::wstring_view msg);
	void Write(std::string_view msg);

private:
	// 파일 쓰기용 스레드
	std::shared_ptr<std::thread> write_thread_;

	TextFile log_file_;

	Concurrency::concurrent_queue<std::string*> log_cq_;
	std::wstring file_name_prefix_;
	std::wstring file_extension_;

	int last_created_file_day_ = -1;
	bool run_thread_ = false;
};

