CIUREA Robert-Mihai - 313CBb
110/135
                    Tema3 SD - Biblioteca online

    Scopul programuluiu il constituie implementarea unei biblioteci online,
folosindu-ne de arbori de prefixe ca structura de stocare de date. Astfel,
utilizam un arbore specializat pe numele cartilor pentru a gasi locul zona
unde urmeza sa fie stocata informatia legata de cartea recomandata spre citire.
In plus, exista un al doilea arbore specializat pe calea data de numele unui autor
pentru ca frunza aferenta ultimului caracter din numele autorului sa stocheze
root-ul unui alt arbore care stocheaza toate cartile autorului, calea fiind data
de numele cartii si frunza finala stocand informatiile legate de carte.

    In vederea implementarii programului, au fost necesare o serie de functii
utilitare menite sa permita realizarea operatiilor pe trie-uri, precum: adaugare
de elemente, cautare de elemente in vederea prelucrarii acestora si afisarea de
elemente. Fisierul trie.c se ocupa de stocarea surselor functiilor operationale,
in timp ce headerul prezinta apelurilor functiilor pentru a putea fi utilizate
in intreg programul.

    trie.c:
    * functia char_int permite conversia unui caracter in valoare intreaga,
    pentru a fi folista in parcurgerea trie-urilor, tinand cont ca calea de
    parcurgere a unui trie este bazat pe avansarea caracter cu caracter, a fost
    realizarea unei conventii pentru a se cunoaste fiecare caracter ce valoare
    numerica are atribuita. Astfel, literele mici ale alfabetului sunt clasificate
    de la 0 la 25, caracterele cu CAPSLOCK de la 26 la 52, si incepant de la 62
    pana la 67 avem semne de ortografie, punctuatie si in final spatiu.

    *functia int_char asigura conversia unei valori intregi in caracter. Aceasta
    functie este benefica cand dorim constructia unui string pe baza caii parcurse
    intr-un trie, de exemplu in necesitatea afisarii autorilor dupa prefix. Se
    aplica conventiile caracterelor in directie inversa.

    *functia alocNode asigura alocarea memoriei necesare in vederea crearii unui
    trie gol, alocand memorie pentur root, pentru vectorul de copii, setand
    informatia din interior ca fiind nula si setand terminatorul de cuvant ca
    fiind 0.

    *functia insert acceseza in mod recursiv trie-ul corespunzator, convertind
    primul caracter al cheii in int astfel incat sa se poata accesa copilul
    corespunzator in vederea introducerii informatiei necesare la copilul
    corespunzator, totodata setand si terminatorul de cuvant ca fiind 1.
    Functia recursiva stie cand sa se opreasca intrucat la fiecare reapel al
    functiei, cheia mai elimina cate un caracter astfel incat functia sa se
    opreasca in momentul in care cheia nu mai are caractere, ajungand la
    copilul corespunzator.

    *functia search cauta in mod recursiva pe baza unei chei in trie-ul dat ca
    parametru in vederea ajungerii la ultimul nod astfel incat sa se returneze
    informatia acelui copil.

    *functia search_pref este ceva mai complexa intrucat aceasta necesita un flag
    care odata ce ajunge 3 se opreste intrucat printre parametrii se regaseste si
    un vector de string-uri care retine maxim primele 3 string-uri gasite pe baza
    unui prefix de nume. Alta modalitate de iesire din recursivitate o constituie
    parametrul out_rule, care primeste valoare de iesire din functie in momentul
    in care ori nu se mai gaseste copil alocat pe baza caracterului din numele dat
    cheie, ori atunci cand flag devine 3. Traversarea trie-ului se face exact ca
    pana acum, ne existand diferente decat in moementul in care se ajunge la
    cazurile probabile de iesire din recursivitate. Cand cheia ajunge goala,
    incepem sa cautam prin copii in vederea gasirii caii necesare de parcurgere
    a trie-ului astfel incat sa se ajunga la nodurile cu informatie. Aceasta metoda
    garanteaza faptul ca elementele gasite sunt in ordine alfabetica.

    Principalele functii care se ocupa de indeplinirea principalelor operatii
ce au loc intr-un dictionar online se afla in fisierul utils.c, cu antetele de
functie in utils.h

    utils.c:
    *functia check_tilda este extremd e importanta intrucat ajuta la separarea
    comenzilor utilitare. Comenzile care intra in categoria auto-complete
    au linia din care fac parte comenzile citite terminata in tilda, spre
    deosebire de comenzile care se bazeaza exclusiv pe nume intregi, concrete.

    *functia create_book citeste din fisierul de input toate informatiile
    aferente unei carti in vederea crearii unei structuri care sa stocheze
    informatiile unei carti, aceasta structura urmand ulterior sa fie introdusa
    in trie-urile necesare.

    *functia add_book insereaza cartea recomandata in primul trie pe baza cheii
    care o constituie numele cartii, pentru ca ulterior sa se caute in trie-ul
    de autori pentru a introduce si in trie-ul aferent autorului carte. Observatia
    o constituie faptul ca daca am citit prima carte care sa apartina unui anumit
    autor, atunci se creeaza calea aferenta autorului si se creaza un trie-ul
    de carti al autorului astfel incat sa se poata introduce informatia necesara.

    *functia search_book cauta in trie-ul corespunzator pe baza cheii citite
    astfel incat sa poata identifica daca cartea cautat exista sau nu,
    iar in cazul in care aceasta exista, afiseaza toate informatiile acesteia,
    in caz contrar aflam ca cartea cautat nu se afla la recomandari.

    *functia search_book_pre cauta pe baza unui prefix toate cartile care corespund
    pattern-ului si daca exista mai mult de 3, atunci functia se opreste intrucat
    functionalitatea acestei functii se bazeaza pe un vector de string-uri in
    care la fiecare identificare de nume care corespunde prefixului, se stocheaza
    acest nume in string la cea mai mica pozitie, dupa care pe baza variabilei
    flag se trece la urmatorul element din vector. Odata ce flag ajunge 3 se iese
    din functia search_pref, pentru a reveni in functia principala unde pe baza
    flag-ului se decide tipul de output. Daca flag este 0 inseamna ca niciodata
    nu s-a gasit vreun string care sa reprezinte un nume de carte, astfel ca se
    afiseaza mesajul aferent, in caz contrar se afiseaza toate numele de carti
    gasite.

    *functia pre_auth_rec cauta in trie-ul de autori primii 3 autori care
    corespund prefixului primit drept cheie, iar deosebirea fata de functia
    precedenta o constituie faptul ca nu mai avem un vector de string-uri,
    ci utilizam un singur string astfel incat sa construim de la 0 numele
    fiecarui autor, si pe masura ce terminam de construi un autor il si
    afisam pentru a incepe reconstructia string-ului in vederea crearii
    noului autor.

    *functia search_author_pre asigura identificarea autorilor gasiti in trie
    pe baza prefixului aferent, iar in cazul in care nu se identifica un astfel
    de autor, atunci se afiseaza mesajul aferent.

    *functia find_titles cauta in mod recursiv toate cartile care exita in trie,
    afisandu-le.

    *functia list_author cauta in trie-ul de autori dac autorul exista, iar in caz
    afirmativ afiseaza toate cartile acestuia care sunt stocate in trie-ul
    autorului.

    *functia search_by_author cauta pe baza autorului in trie-ul de autori, iar
    daca autorul exista atunci se cauta in trie-ul aferent acestuia de carti daca
    titlul cautat exista, iar in caz afirmativ se afiseaza informatiile aferente
    cartii.

    *functia search_by_athor_pref verifica daca autorul exista in trie-ul de
    autori, iar in caz afirmativ, pe baza prefixului de carte citit de la
    tastatura se incearca identificarea a maxim 3 carti scrise de acest autor
    care corespund prefixului dat drept cheie.

    Functionalitatea programului este asigurata de main-ul programului in care
pe baza mai multor structuri decizionale se face idenntificarea functiilor ce
sunt necesare a fi apelate in scopul realizarii task-urilor aferente
dictionarului online.