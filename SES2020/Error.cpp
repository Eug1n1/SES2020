#pragma once
#include "pch.h"

namespace Error
{
	//серии ошибок: 0 - 99  -  системные ошибки 
	//			  100 - 109 -  ошибки параметров
	//		      110 - 119 -  ошибки открытия и чтения файлов
	ERROR errors[ERROR_MAX_ENTRY] = // таблица ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY 
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY(2, "Не удалось открыть out файл"),
		ERROR_ENTRY(3, "Превышена длина входного параметра"),
		ERROR_ENTRY(4, "Параметр -in должен быть задан"),
		ERROR_ENTRY(5, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(6, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Таблица лексем переполнена"),
		ERROR_ENTRY(201, "Нераспознанная лексема"),
		ERROR_ENTRY(202, "Таблица идентификаторов переполнена"),
		ERROR_ENTRY(203, "Перезапись идентификатора"),
		ERROR_ENTRY(204, "Выход за границу таблицы лексем (или идентификаторов)"),
		ERROR_ENTRY(205, "Не удалось создать файл с лексемами (или идентификаторами)"),
		ERROR_ENTRY(206, "Слишком длинный литерал"),
		ERROR_ENTRY(207, "Неверный формат строкового литерала"),
		ERROR_ENTRY(208, "Слишком длинное имя переменной"),
		ERROR_ENTRY(209, "Неизвестная переменная"),
		ERROR_ENTRY(210, "Недопустимый идентификатор"),
		ERROR_ENTRY_NODEF(211), ERROR_ENTRY_NODEF(212), ERROR_ENTRY_NODEF(213), ERROR_ENTRY_NODEF(214), ERROR_ENTRY_NODEF(215),
		ERROR_ENTRY_NODEF(216), ERROR_ENTRY_NODEF(217), ERROR_ENTRY_NODEF(218), ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Неверная структура программы"),
		ERROR_ENTRY(301, "Ошибочный сепаратор"),
		ERROR_ENTRY(302, "Ошибка в выражении"),
		ERROR_ENTRY(303, "Ошибка в параметрах функции"),
		ERROR_ENTRY(304, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(305),
		ERROR_ENTRY_NODEF(306),
		ERROR_ENTRY_NODEF(307),
		ERROR_ENTRY_NODEF(308),
		ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY(400, "Return не может возвращать функцию"),
		ERROR_ENTRY(401, "Ошибка в аргументах вызываемой функции функции"),
		ERROR_ENTRY(402, "Нельзя присвоить значение данного типа"),
		ERROR_ENTRY(403, "Недопустимый тип аргумента цикла"),
		ERROR_ENTRY(404, "Недопустимое количество аргументов функции"),
		ERROR_ENTRY_NODEF10(405), ERROR_ENTRY_NODEF10(406),
		ERROR_ENTRY_NODEF(407), ERROR_ENTRY_NODEF(408), ERROR_ENTRY_NODEF(409),
		ERROR_ENTRY_NODEF10(410), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF10(450),
		ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480), ERROR_ENTRY_NODEF10(490),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800)
	};
	ERROR geterror(int id) {
		ERROR err;
		if (id < 0 || id > ERROR_MAX_ENTRY) {
			err.id = errors[0].id;
			strcpy_s(err.message, errors[0].message);
		}
		else {
			err.id = errors[id].id;
			strcpy_s(err.message, errors[id].message);
		}
		return err;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		ERROR err;
		if (id < 0 || id > ERROR_MAX_ENTRY) {
			err.id = errors[0].id;
			strcpy_s(err.message, errors[0].message);
		}
		else {
			err.id = errors[id].id;
			strcpy_s(err.message, errors[id].message);
		}
		err.inext.line = line + 1;
		err.inext.col = col;
		return err;
	}
}