#include "pch.h"
#include "FileLogger.h"

FileLogger::FileLogger() 
{
}

FileLogger::~FileLogger()
{
	while (!log_cq_.empty())
	{
		std::string* msg_ptr = nullptr;
		if (log_cq_.try_pop(msg_ptr))
		{
			if (msg_ptr == nullptr)
			{
				CRASH();
				return;
			}

			log_file_.Write(*msg_ptr);
			SAFE_DELETE(msg_ptr);
		}
	}
	log_file_.CloseFile();
}

bool FileLogger::MakeFile(const CTime& curTime)
{
	// 최초 파일을 생성할때와, 로그기록중 날짜가 변경되는 경우에 호출되므로
	// 기존파일이 있으면 먼저 닫음
	log_file_.CloseFile();


	std::wstring cur_date_str(std::format(L"{}{:02}{:02}",
		curTime.GetYear(), curTime.GetMonth(), curTime.GetDay()));

	std::wstring log_path(std::format(L"logs\\{0}", cur_date_str));

	// 디렉토리 없으면 생성
	if (!PathFileExistsW(log_path.c_str()))
	{
		SHCreateDirectoryExW(NULL, log_path.c_str(), NULL);
	}

	std::wstring cur_time_str(std::format(L"{:02}{:02}{:02}",
		curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond()));


	std::wstring fullPath = std::format(L"{0}\\{1}_{2}_{3}.{4}",
		log_path, file_name_prefix_, cur_date_str, cur_time_str, file_extension_);

	log_file_.Create(fullPath);
	last_created_file_day_ = curTime.GetDay();
    return true;
}

void FileLogger::ThreadStart()
{
	run_thread_ = true;
	MakeFile(CTime::GetCurrentTime());
	write_thread_ = std::make_shared<std::thread>(std::bind(&FileLogger::ThreadLoop, this));
}

void FileLogger::ThreadLoop()
{
	while (run_thread_)
	{
		while (!log_cq_.empty())
		{
			std::string* msg_ptr = nullptr;
			if (log_cq_.try_pop(msg_ptr))
			{
				if (msg_ptr == nullptr)
				{
					CRASH();
					return;
				}

				log_file_.Write(*msg_ptr);
				SAFE_DELETE(msg_ptr);
			}
		}
	}
}

void FileLogger::ThreadStop()
{
	run_thread_ = false;
	if (write_thread_)
	{
		if (write_thread_->joinable())
		{
			write_thread_->join();
		}
	}

	while (!log_cq_.empty())
	{
		std::string* msg_ptr = nullptr;
		if (log_cq_.try_pop(msg_ptr))
		{
			if (msg_ptr == nullptr)
			{
				CRASH();
				return;
			}

			log_file_.Write(*msg_ptr);
			SAFE_DELETE(msg_ptr);
		}
	}
	log_file_.CloseFile();
}

void FileLogger::Init(std::wstring_view file_name_prefix, std::wstring_view file_extension)
{
	file_name_prefix_ = file_name_prefix;
	file_extension_ = file_extension;
}


void FileLogger::Write(std::wstring_view msg)
{
	// UTF8 형식으로 파일을 저장하기 떄문에..
	Write(WstringToUtf8(msg.data()));
}

void FileLogger::Write(std::string_view msg)
{

	// 포인터로 만들어서 저장
	// 나중에 queue에서 뺄때 delete해줘야함

	std::string* log_ptr = new std::string(std::format("{}\n", msg));

	CTime cur_time = CTime::GetCurrentTime();

	if (cur_time.GetDay() != last_created_file_day_)
	{
		MakeFile(cur_time);
	}

	log_cq_.push(log_ptr);

}
