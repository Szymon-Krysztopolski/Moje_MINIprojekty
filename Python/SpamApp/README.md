# SpamApp

## Wstęp
Program umożliwia pisanie tekstu w sposób zautomatyzowany. Treść pobierana jest z odpowiednich plików. Zaimplementowano sterowanie za pomocą terminala CMD.
Do skorzystania z programu potrzebny będzie język programowania Python, oraz system operacyjny Windows.

### Uwaga!
Skrypt został przygotowany wyłączne w celach edukacyjnych. Autor nie ma na celu propagowanie szkodliwych zachowań, ani nie bierze odpowiedzialności za potencjalne szkody wyrządzone przez przedstawiony program.

## Opis
Program umożliwia kilka opcji umożliwiające szybkie pisanie, oraz oferuje zarządzanie zmiennymi z których korzysta program.

* 1\. `fastSpam` - po określonej liczbie sekund (określonej przez zmienną `DelayBeforeSpam`) wykonuje się automatyczne pisanie zawartości pliku `FileName` na standardowe wyjście. Pisanie odbywa się do miejsca gdzie aktualnie jest focus. To ile razy wartość z pliku zostanie powtórzona zawarte jest w zmiennej `Loops`.
* 2\. `manualSpam` - opcja umożliwiająca na automatyczne skanowanie klawiatury. Przy naciśnięciu spacji wklejany jest tekst z pliku którego nazwa jest zawarta w zmiennej `FileNameManualSpam`. Po naciśnięciu przycisku `e` użytkownik wraca do menu głównego.
* 3\. `change settings` - zmień wartości aktualnie używanych zmiennych
* 4\. `show settings` - pokaż aktualne wartości zmiennych
* 5\. `reset program` - ustawienia początkowe
* e. `exit` - wyłączenie aplikacji

## Dodatkowe informacje
* Wszelkie zmienne oraz ograniczenia co do ich wartości zawarte są w pliku `constants.py`.
* Plik `start.bat` umożliwia automatyczne pobranie wymaganych bibliotek i włączenie terminala w odpowiednim miejscu, aby możliwe było włączenie aplikacji.
* Aplikacje wpłącza się za pomocą komency `python .\main.py`.