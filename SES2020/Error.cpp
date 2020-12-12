#pragma once
#include "pch.h"

namespace Error
{
	//����� ������: 0 - 99  -  ��������� ������ 
	//			  100 - 109 -  ������ ����������
	//		      110 - 119 -  ������ �������� � ������ ������
	ERROR errors[ERROR_MAX_ENTRY] = // ������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������"), // ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY 
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY(2, "�� ������� ������� out ����"),
		ERROR_ENTRY(3, "��������� ����� �������� ���������"),
		ERROR_ENTRY(4, "�������� -in ������ ���� �����"),
		ERROR_ENTRY(5, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(6, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "������������ ������ � �������� ���� (-in)"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "������� ������ �����������"),
		ERROR_ENTRY(201, "�������������� �������"),
		ERROR_ENTRY(202, "������� ��������������� �����������"),
		ERROR_ENTRY(203, "���������� ��������������"),
		ERROR_ENTRY(204, "����� �� ������� ������� ������ (��� ���������������)"),
		ERROR_ENTRY(205, "�� ������� ������� ���� � ��������� (��� ����������������)"),
		ERROR_ENTRY(206, "������� ������� �������"),
		ERROR_ENTRY(207, "�������� ������ ���������� ��������"),
		ERROR_ENTRY(208, "������� ������� ��� ����������"),
		ERROR_ENTRY(209, "����������� ����������"),
		ERROR_ENTRY(210, "������������ �������������"),
		ERROR_ENTRY_NODEF(211), ERROR_ENTRY_NODEF(212), ERROR_ENTRY_NODEF(213), ERROR_ENTRY_NODEF(214), ERROR_ENTRY_NODEF(215),
		ERROR_ENTRY_NODEF(216), ERROR_ENTRY_NODEF(217), ERROR_ENTRY_NODEF(218), ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "�������� ��������� ���������"),
		ERROR_ENTRY(301, "��������� ���������"),
		ERROR_ENTRY(302, "������ � ���������"),
		ERROR_ENTRY(303, "������ � ���������� �������"),
		ERROR_ENTRY(304, "������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF(305),
		ERROR_ENTRY_NODEF(306),
		ERROR_ENTRY_NODEF(307),
		ERROR_ENTRY_NODEF(308),
		ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY(400, "Return �� ����� ���������� �������"),
		ERROR_ENTRY(401, "������ � ���������� ���������� ������� �������"),
		ERROR_ENTRY(402, "������ ��������� �������� ������� ����"),
		ERROR_ENTRY(403, "������������ ��� ��������� �����"),
		ERROR_ENTRY(404, "������������ ���������� ���������� �������"),
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