#include "stdafx.h"
#include "Error.h"

namespace Error
{
  // ñåğèè îøèáîê: 0 - 99 - ñèñòåìíûå îøèáêè
  //               100 - 109 - îøèáêè ïàğàìåòğîâ
  //               110 - 119 - îøèáêè îòêğûòèÿ è ÷òåíèÿ ôàéëîâ
    ERROR_ errors[ERROR_MAX_ENTRY] = // òàáëèöà îøèáîê
  {
      ERROR_ENTRY(0, "Íåäîïóñòèìûé êîä îøèáêè"),
      ERROR_ENTRY(1, "Ñèñòåìíûé ñáîé"),
      ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
      ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
      ERROR_ENTRY_NODEF(10), ERROR_ENTRY_NODEF(20), ERROR_ENTRY_NODEF(30), ERROR_ENTRY_NODEF(40), ERROR_ENTRY_NODEF(50),
      ERROR_ENTRY_NODEF(60), ERROR_ENTRY_NODEF(70), ERROR_ENTRY_NODEF(80), ERROR_ENTRY_NODEF(90),
      ERROR_ENTRY(99,  "Íåäîïóñòèìûé ïóòü ê ôàéëó .asm"),
      ERROR_ENTRY(100, "Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
      ERROR_ENTRY(101, "Îøèáêà îòêğûòèÿ ôàéëà - out"),
      ERROR_ENTRY(102, "Êîëè÷åñòâî ñèìâîëîâ â èñõîäíîì ôàéëå áîëüøå äîïóñòèìîãî çíà÷åíèÿ"),
      ERROR_ENTRY(103, "Ğàçìåğ òàáëèöû èäåíòèôèêàòîğîâ ïåğåïîëíåí (ìàêñèìóì: 4096)"),
      ERROR_ENTRY(104, "Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),
      ERROR_ENTRY(105, "Ğàçìåğ òàáëèöû ëåêñåì ïåğåïîëíåí (ìàêñèìóì: 4096)"),
      ERROR_ENTRY(106, "Öåïî÷êà íå ğàñïîçíàíà"),
      ERROR_ENTRY(107, "Íåïğàâèëüíîå îïğåäåëåíèå èäåíòèôèêàòîğà"),
      ERROR_ENTRY(110, "Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
      ERROR_ENTRY(111, "Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
      ERROR_ENTRY(112, "Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
      ERROR_ENTRY(200, "Äëèíà èäåíòèôèêàòîğà íå ìîæåò áûòü áîëüøå 15"),
      ERROR_ENTRY(201, "Ïåğåîïğåäåëåíèå èäåíòèôèêàòîğà"),
      ERROR_ENTRY(202, "Íåîáúÿâëåííûé èäåíòèôèêàòîğ"),
      ERROR_ENTRY(203, "Ñëèøêîì áîëüøàÿ äëèíà ó string-ëèòåğàëà"),
      ERROR_ENTRY(204, "Íåñîîòâåòñòâèå ôîğìàëüíûõ è ôàêòè÷åñêèõ ïàğàìåòğîâ ôóíêöèè"),
      ERROR_ENTRY(205, "Íåäîïóñòèìàÿ îïåğàöèÿ â âûğàæåíèè"),
      ERROR_ENTRY(206, "Íåâîçìîæíî ïğåîáğàçîâàòü òèï â âûğàæåíèè"),
      ERROR_ENTRY(207, "Íåäîïóñòèìûé âîçâğàùàşùèé òèï â ôóíêöèè"),
      ERROR_ENTRY(208, "Íåäîïóñòèìîå èñïîëüçîâàíèå óíàğíîãî ìèíóñà"),
      ERROR_ENTRY(209, "Íåäîïóñòèìûé àğãóìåíò âûâîäà â ñòàíäàğòíûé ïîòîê"),
      ERROR_ENTRY_NODEF(400),
      ERROR_ENTRY(500, "Ôóíêöèÿ ñòàíäàğòíîé áèáëèîòåêè íå íàéäåíà"),
      ERROR_ENTRY(600, "Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû"),
      ERROR_ENTRY(601, "Îøèáî÷íûé îïåğàòîğ"),
      ERROR_ENTRY(602, "Îøèáêà â âûğàæåíèè"),
      ERROR_ENTRY(603, "Îøèáêà â ïîäâûğàæåíèè"),
      ERROR_ENTRY(604, "Îøèáêà â ïàğàìåòğàõ ôóíöèè"),
      ERROR_ENTRY(605, "Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè"),
      ERROR_ENTRY(606, "Îøèáêà â âûğàæåíèè ñğàâíåíèÿ"),
      ERROR_ENTRY(607, "Îøèáêà â ñòğóêòóğå öèêëà for"),
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