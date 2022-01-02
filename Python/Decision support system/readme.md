# Decision support system - my proposition of algorithm
Algorytm wspomagania decyzji - Na wejściu podajemy ranking ważności kryteriów wraz z progami nierozróżnialności dla każdego. Progi te są potrzebne, aby na ich podstawie przypisywać warianty do poszczególnych klas. Następnie po kolei w pętli analizuje się się warianty tylko pod kątem jednego kryterium (zaczynając od najbardziej istotnego) i przypisuje się je do danej klasy tworząc ranking. W tym momencie każdy wariant z klasy wyższej jest na pewno lepszy od tych z klasy niżej. Później w obrębie każdej z klas wykonuje się tą samą analizę pod kątem następnego kryterium. Algorytm kończy się po wyczerpaniu kryteriów, lub utworzeniu podklas z pojedynczymi wariantami. Przebieg algorytmu ściśle zależy od kolejności analizowanych kryteriów. Jeśli wariant jest dobry tylko na najważniejszym kryterium wady na pozostałych nie będą tak karane jak w przypadku innych metod wspomagania decyzji.

Algorytm wymyśliłem samodzielnie na potrzeby analizy swojego zbioru danych.  Algorytm ten jest z rodziny algorytmów wspomagania decyzji do której należą chociażby: UTA, ASSESS, ELECTRE Is, ELECTRE Tri

## Plik wejściowy zawiera:
* rodzaj kryteriów (g - gain, c - cost)
* nagłówki
* kolejne warianty

---

## Opis analizowanego problemu
Analiza, której celem jest wyłonienie najlepszej broni z obecnie dostępnych w grze Brawlhalla. Wariantów jest 13. Jest cały dostępny zbiór danych.

### Przykładowy wariant: 
Sword. Podstawowy typ oręża. Średnie obrażenia są stosunkowo niskie, wynoszą 14,8 punktów DMG. Ataki są stosunkowo szybkie. Sword jest dostępny dla 11 różnych postaci. Współczynnik zwycięstw do porażek jest równym 49,28. Społeczność w badaniu określiła poziom skomplikowania tego oręża na dość niski, ponieważ zaledwie 3 punkty na 10 maksymalnie.

## Kryteria w problemie
- Damage – każda broń ma kilka rodzajów ataków, każdy ma swoje określone obrażenia. Po zebraniu informacji o obrażeniach każdego ataku każdej broni wykonano średnią ważoną. Wagi dobrano na podstawie preferencji decydenta (wyższa waga, bardziej istotny atak / częściej wykonywany).

- Attack Speed – stworzone przez decydenta. Każdy oręż ma określoną prędkość ataku. Kryterium jest uogólnione do trzech wartości. Broń może być szybka, wolna lub mieć normalną prędkość. Decyzja o klasie została podjęta na podstawie ogólnego wrażenia z prędkości broni podczas kilkuset godzin spędzonych w grze i rozegraniu wielu meczy każdym typem oręża.

- HMC – How many champions have this weapon. Parametr obliczony na podstawie informacji z gry.

- Winrate – globalny współczynnik wygranych gier dla danej broni.

- TTL – time to lern. Kryterium to określa jak wiele czasy należy poświęcić, aby nauczyć się danej broni. Wyniki pozyskane za pomocą ankiety.
