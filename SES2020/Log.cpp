#include "pch.h"

namespace Log {
	LOG Getlog(wchar_t logfile[]) {
		Log::LOG log;
		wcscpy_s(log.logfile, logfile);
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
			throw ERROR_THROW(112);
		return log;
	}
	void WriteLine(LOG log, const char* c, ...) {
		const char** buf = &c;
		char str[300]{};
		while (strcmp(*buf, "")) {
			strcat_s(str, *buf);
			buf++;
		}
		*log.stream << str;
	}			
	void WriteLine(LOG log, const wchar_t* c, ...) {
		const wchar_t** buf = &c;
		size_t i = 0;
		char str[300]{};
		char bufBuf[100]{};
		sprintf_s(bufBuf, "%ws", *buf);
		while (strcmp(bufBuf, "")) {
			sprintf_s(bufBuf, "%ws", *buf);
			strcat_s(str, bufBuf );
			buf++;
		}
		*log.stream << str;
	}
	void WriteLog(LOG log) {
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80]{};
		time(&rawtime);
		localtime_s(&timeinfo ,&rawtime);
		strftime(buffer, 80, "Дата: %d.%m.%Y %X", &timeinfo);
		*log.stream << "\n---- Протокол ---- " << buffer << " ----\n";
	}
	void WriteParm(LOG log, Parm::PARM parm) {
		char str[PARM_MAX_SIZE];
		*log.stream << "---- Параметры ----\n";
		sprintf_s(str, "%ws", parm.log);
		*log.stream << "-log: " << str << std::endl;
		sprintf_s(str, "%ws", parm.out);
		*log.stream << "-out: " << str << std::endl;
		sprintf_s(str, "%ws", parm.in);
		*log.stream << "-int: " << str << std::endl;
	}
	void WriteIn(LOG log, In::IN in) {
		*log.stream << "---- Исходные данные ----\n";
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано: " << in.ignor << std::endl;
		*log.stream << "Количество строк: " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error) {
		if (!log.stream)
			std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line;
		else
			*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col;
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
		log.stream = nullptr;
	}
}