#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

Parm::PARM Parm::getparm(int argc, _TCHAR* argv[])
{
  if (argc > 1) {
    PARM parm;
    if (wcsstr(argv[1], PARM_IN)) {

      for (int i = 1; i < argc; i++) {
        if (wcslen(argv[i]) > PARM_MAX_SIZE) {
          throw ERROR_THROW(104);
        }
      }

      for (int i = 0; argv[1][i] != '\0'; i++) {
        parm.in[i] = argv[1][i + wcslen(PARM_IN)];
      }

      bool parm_out = false;
      bool parm_log = false;
      for (int i = 2; i < argc; i++) {
        if (wcsstr(argv[i], PARM_OUT)) {
          for (int j = 0; argv[i][j] != '\0'; j++) {
            parm.out[j] = argv[i][j + wcslen(PARM_OUT)];
          }
          parm_out = true;
        }
        else if (wcsstr(argv[i], PARM_LOG)) {
          for (int j = 0; argv[i][j] != '\0'; j++) {
            parm.log[j] = argv[i][j + wcslen(PARM_LOG)];
          }
          parm_log = true;
        }
      }

      if (!parm_out) {
        wcscpy_s(parm.out, parm.in);
        wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, wcslen(parm.out) + wcslen(PARM_OUT) + 1);
      }
      if (!parm_log) {
        wcscpy_s(parm.log, parm.in);
        wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(parm.log) + wcslen(PARM_LOG) + 1);
      }

    }
    else {
      throw ERROR_THROW(100);
    }
    return parm;
  }
  else {
    throw ERROR_THROW(100);
  }
}