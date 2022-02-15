# Problem komiwojażera
Jest to problem NP-zupełny polegający na znalezieniu minimalnego cyklu Hamiltona w pełnym grafie ważonym. W skrócie problem ten polega na rozpoczęciu podróży w jakimś punktcie (np. mieście), a naszym celem jest dotarcie do wszystkich pozostałych punktów na mapie (tylko raz), oraz powrót do początkowego punktu. 
<p align="center">
  <img src="https://github.com/Szymon-Krysztopolski/Moje_MINIprojekty/blob/main/C%26C%2B%2B/Problem%20komiwojazera/zdj1.png" />
</p>

## Reprezentacja problemu
Problem może zostać przedstawiony za pomocą macierzy sąsiedztwa. Jest to macież NxN, która zawiera odległości od miasta X do każdego pozostałego. Macierz ta jest symetryczna względem głównej przekątnej (ponieważ z miasta A do B jest taka sam odległość jak z miasta B do A), oraz na głównej przekątnej występują zera (ponieważ miasto A jest oddalone od samego siebie o dokładnie 0). Można zatem kożystać jedynie z górnego/dolnego trójkąta macierzy.

## Zastosowane rozwiązania
### Algorytm zachłanny
Jest to algorytm dość prosty w swoich założeniach. Algorytmy zachłanne to zbiór algorytmów w których następnym krokiem algorytmu jest obecnie najlepsza opcja. Dla problemy TSP (komiwojażera) będzie to wybór najbliższego nieodwiedzonego miasta/punktu. Algorytm ten ma złożoność liniową i daje dość dobre wyniki, jednakże możliwe jest znalezienie lepszego rozwiązania.

### Algorytm zachłanny + Tabu search
Tabu search jest metaheurystyką którą można zastosować przy okazji poszukowania rozwiązania jakiegoś problemu. Polega ona na poszukiwaniu możliwe jak najlepszego rozwiązania, jednakże w odróżnieniu od algorytmu zachłannego pozwala na tymczasowe pogorszenie wyniku. Właściwość tą zapewnia nam tzw. tablica tabu. Tablca ta zapisuje ostatnio wykonane ruchy (np zamiane kolejności odwiedzanych miast) i uniemożliwia powtówrzenie ich przez kilka następnych wywołań algorytmu przeszukiwania. Jest to sposób na wyjście z lokalnego minimum. Czym większa tablica tabu tym algorytm jest w stanie próbować więcej różnych nieodwiedzonych ścieżek. Mniejszy rozmiar tablicy tabu sprawia, że algorytm dokładniej przeszukuje obszar obecnego lokalnego minimum.  Głównymi parametrami które mają wpływ na przebieg procesu przeszukiwania w przypadku metaheurystyki tabu search jest rozmiar tablicy, oraz liczba iteracji algorytmu (czym więcej tym potencjalnie lepsze rozwiązanie). W przypadku TSP w każdym kroku pętli testuje się inną permutację punktów. Przykładowo dana jest ścieżka A-C-D-B-E-A. Zamienia się punkt A z punktem B. Teraz sprawdzamy ścieżkę B-C-D-A-E-B. Najlepsza uzyskana w ten sposób ściezka będzie naszym kolejnym stanem wejściowym. 

## Program
W pliku main.cpp znajduje się program który stosuje wyżej wymienione metody. Funckja która zawiera heurystyke tabu search zaczyna od znalezieniu pierwszego rozwiązania za pomocą algorytmy zachłannego. Następnie w pętli (ilość kroków można zmienić w kodzie) sprawdza potencjalne poprawy z wykorzystaniem tablicy tabu (jej rozmiar można zmienić w kodzie, skaluje się on w zależność od ilości punktów, zakres 5%-50%).

## Potencjalne ulepszenie 
Aktualnie program wykorzystuje do poprawienia wyniku przegląd wszystkich możliwych kombinacji zmiany kolejności miast. Ten etap jest najbardziej czasochłonny. Sugeruje wyliczenie na samym początku macierz potencjalnych zmian, która będzie zawierała możliwe zamiany kolejności 2 miast oddalinych od siebie o nie więcej niż R. Jest to intuicyjne rozwiązanie, poniważ zakładający że mamy cykl A-B-C-A, dzie A i B są od siebie oddalone o 10km, a odległość do C wynosi 1000km to nie ma sensu rozważać drogi A-C-B-A.
