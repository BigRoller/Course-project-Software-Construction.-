#include "stdafx.h"
#include "Error.h"

namespace Error
{
  // ����� ������: 0 - 99 - ��������� ������
  //               100 - 109 - ������ ����������
  //               110 - 119 - ������ �������� � ������ ������
    ERROR_ errors[ERROR_MAX_ENTRY] = // ������� ������
  {
      ERROR_ENTRY(0, "������������ ��� ������"),
      ERROR_ENTRY(1, "��������� ����"),
      ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
      ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
      ERROR_ENTRY_NODEF(10), ERROR_ENTRY_NODEF(20), ERROR_ENTRY_NODEF(30), ERROR_ENTRY_NODEF(40), ERROR_ENTRY_NODEF(50),
      ERROR_ENTRY_NODEF(60), ERROR_ENTRY_NODEF(70), ERROR_ENTRY_NODEF(80), ERROR_ENTRY_NODEF(90),
      ERROR_ENTRY(99,  "������������ ���� � ����� .asm"),
      ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
      ERROR_ENTRY(101, "������ �������� ����� - out"),
      ERROR_ENTRY(102, "���������� �������� � �������� ����� ������ ����������� ��������"),
      ERROR_ENTRY(103, "������ ������� ��������������� ���������� (��������: 4096)"),
      ERROR_ENTRY(104, "��������� ����� �������� ���������"),
      ERROR_ENTRY(105, "������ ������� ������ ���������� (��������: 4096)"),
      ERROR_ENTRY(106, "������� �� ����������"),
      ERROR_ENTRY(107, "������������ ����������� ��������������"),
      ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
      ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
      ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),
      ERROR_ENTRY(200, "����� �������������� �� ����� ���� ������ 15"),
      ERROR_ENTRY(201, "��������������� ��������������"),
      ERROR_ENTRY(202, "������������� �������������"),
      ERROR_ENTRY(203, "������� ������� ����� � string-��������"),
      ERROR_ENTRY(204, "�������������� ���������� � ����������� ���������� �������"),
      ERROR_ENTRY(205, "������������ �������� � ���������"),
      ERROR_ENTRY(206, "���������� ������������� ��� � ���������"),
      ERROR_ENTRY(207, "������������ ������������ ��� � �������"),
      ERROR_ENTRY(208, "������������ ������������� �������� ������"),
      ERROR_ENTRY(209, "������������ �������� ������ � ����������� �����"),
      ERROR_ENTRY_NODEF(400),
      ERROR_ENTRY(500, "������� ����������� ���������� �� �������"),
      ERROR_ENTRY(600, "�������� ��������� ���������"),
      ERROR_ENTRY(601, "��������� ��������"),
      ERROR_ENTRY(602, "������ � ���������"),
      ERROR_ENTRY(603, "������ � ������������"),
      ERROR_ENTRY(604, "������ � ���������� ������"),
      ERROR_ENTRY(605, "������ � ���������� ���������� �������"),
      ERROR_ENTRY(606, "������ � ��������� ���������"),
      ERROR_ENTRY(607, "������ � ��������� ����� for"),
      ERROR_ENTRY_NODEF(700),
      ERROR_ENTRY_NODEF(800),
      ERROR_ENTRY_NODEF(900)
        };
    
    ERROR_ geterror(int id) {
      if (id >= 0 && id <= ERROR_MAX_ENTRY) {
        for (int i = 0; i <= ERROR_MAX_ENTRY; i++) {
          if (abs(errors[i].id) == id) {
            return errors[i];
          }
        }
      }
      else {
        return errors[0];
      }
  }
    ERROR_ geterrorin(int id, int line = -1, int col = -1) {
      if (id >= 0 && id <= ERROR_MAX_ENTRY) {
        for (int i = 0; i <= ERROR_MAX_ENTRY; i++) {
          if (abs(errors[i].id) == id) {
            ERROR_ err = errors[i];
            err.inext.col = col;
            err.inext.line = line;
            return err;
          }
        }
      }
      else {
        return errors[0];
      }
  }
}