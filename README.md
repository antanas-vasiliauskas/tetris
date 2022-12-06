PANEVĖŽIO JUOZO BALČIKONIO GIMNAZIJA

Projektinis darbas

# **Žaidimo kūrimas naudojant C++**

# **programavimo kalbą**

**Antanas Vasiliauskas IIIf**

**Augustinas Jarockis IIIe**

Vadovė Renata Burbaitė

Panevėžys

2021

# Turinys

[**Įvadas**  **3**](#_Toc73875048)

[**Darbo tikslas**  **3**](#_Toc73875049)

[**Naudojamos programos ir C++ bibliotekos**  **4**](#_Toc73875050)

[**Darbo eiga**  **5**](#_Toc73875051)

[**Projekto paruošimas ir sukonfigūravimas**  **5**](#_Toc73875052)

[**Abstrakcijų kūrimas**  **6**](#_Toc73875053)

[„ **Tetris" žaidimo logikos kūrimas**  **8**](#_Toc73875054)

[**Scenų valdymo sistemos ir meniu kūrimas**  **9**](#_Toc73875055)

[**Žaidimo gerinimas**  **10**](#_Toc73875056)

[**Autonominės programos, žaidžiančios žaidimą, kūrimas**  **11**](#_Toc73875057)

[**Tobulinimo galimybės**  **11**](#_Toc73875058)

[**Išvados**  **11**](#_Toc73875059)

[**Ateities Planai**  **12**](#_Toc73875060)

[**Informacijos šaltiniai**  **13**](#_Toc73875061)

# Įvadas

Šiais laikais programavimo srityje sparčiai populiarėja įvairūs programinės įrangos kūrimo įrankiai, žymiai spartinantys programuotojo darbą. Dažniausiai šie įrankiai už programuotoją atlieka didžiąją darbo dalį: norint sukurti svetainę, užtenka pasirinkti turinio valdymo sistemos (Wordpress ar kt.) temą ir įdiegti funkcionalumo įskiepius. Norint sukurti žaidimą, galima naudoti žaidimų variklį (ang. Game engine), kuris pasirūpina tokiais dalykais kaip kompiuterinės grafikos vaizdavimu (ang. rendering), žaidimo scenų valdymu (ang. Scene management), laiko parinkimu, kada atnaujinti vaizdo kadrą, registruoti žaidėjo įvesti ir t.t. Šios platformos sutaupo daug laiko ir padeda išvengti nereikalingų rūpesčių programuotojams, tačiau jų naudojimas turi ir neigiamų pusių. Visų pirma, programuotojo įgyjamos žinios naudojantis tokiomis platformomis yra mažiau vertingos. Kadangi jos atlieka didžiąją dalį darbo suteikdamos abstrakcijas, tai programuotojas veikiau išmoksta, kaip dirbti su tomis platformomis, o ne universalių programavimo žinių ir paradigmų, kurias galėtų panaudoti už šių platformų ribų. Šios platformos taip pat gali apriboti programuotoją, kadangi jis naudojasi aplinka, kurią sukūrė kiti žmonės, tad gali kilti problemų bandant išplėsti jos funkcionalumą, norint pridėti į projektą tai, ko platforma nesiūlo. Dažnai nutinka taip, kad programuotojas, užuot galvojęs, kaip išspręsti problemą, galvoja, kur galėtų surasti dar vieną programavimo įrankį ar biblioteką, kuri padarytų darbą už jį.

Šio mūsų projektinio darbo tikslas – atsiriboti nuo tokių platformų ir sukurti visiems gerai žinomą 1984 metų žaidimą „Tetris". Jį kurti C++ programavimo kalba, stengtis naudoti kuo mažiau pagalbinių programų ir parašyti didžiąją dalį programos logikos patiems.

# Darbo tikslas

• Sukurti žaidimą be žaidimo variklio ir naudojant kuo mažiau pagalbinių programų.

• Įgyti žinių apie kompiuterinės grafikos, abstrakcijų ir sistemų kūrimą.

• Įgyti žinių dirbant su C++ programavimo kalba.

• Įgyti įgūdžių, kaip tvarkyti ir išlaikyti organizuotą struktūrą didelės apimties projekte.

• Sukurti autonominę programą, galinčią žaisti mūsų sukurtą žaidimą geriau nei žmogus.

# Naudojamos programos ir C++ bibliotekos

Kurdami žaidimą neišsivertėme be šių pagalbinių programų:

![](RackMultipart20221206-1-khe6h8_html_6a9329144b9094d4.jpg)

_pav. 1: Visual Studio logotipas_

**Visual Studio 2017**

- Kodo redagavimo įrankis, kuris paryškina C++ kalbos sintaksę ir rodo klaidas.
- Palengvina programos kompiliavimo procesą, tad nereikia pačiam kompiliuoti programos per komandinę eilutę.

_pav. 2: GitHub logotipas_

**G ![](RackMultipart20221206-1-khe6h8_html_95d6e93a02b0d2e9.png) itHub**

- Leidžia patikimai saugoti skirtingas programos versijas vienoje vietoje.
- Leidžia vienu metu dirbti keliems žmonėms prie to pačio projekto ir vėliau sujungti pakeitimus.

![](RackMultipart20221206-1-khe6h8_html_afcc9a1157c1f829.png)

**OpenGL GLEW ir GLFW C++ bibliotekos**

- Suteikia bazines funkcijas, tokias kaip tuščio programos lango sukūrimas, 2D figūrų braižymas nurodant RGB spalvą bei figūros viršūnių koordinates ir pan.
_pav. 3: Projekte naudojamos bibliotekos_
- ![](RackMultipart20221206-1-khe6h8_html_feda0ee657bc586b.png)Suteikia funkcijas, palengvinančias naudotojo klaviatūros įvesties fiksavimą.
- stb\_image biblioteka leidžianti paveiksliukus paversti tekstūromis.

![](RackMultipart20221206-1-khe6h8_html_8e9e7a313eefd8b6.jpg)

**Inkscape ir Pixlr grafikos kūrimo programos**

- ![](RackMultipart20221206-1-khe6h8_html_f550bcc75b759b70.png)Suteikia įrankius, leidžiančius sukurti žaidimui naudojamus paveikslėlius.

_pav. 4: Grafikos kūrimo programų logotipai_

# Darbo eiga

Visą darbo eigą galima suskirstyti į šiuos mažesnius tikslus, kuriuos teko įvykdyti:

1. **Projekto paruošimas ir sukonfigūravimas**
2. **Abstrakcijų kūrimas**
3. „ **Tetris" žaidimo logikos kūrimas**
4. **Scenų valdymo sistemos ir meniu kūrimas**
5. **Žaidimo gerinimas**
6. **Autonominės programos, žaidžiančios žaidimą, kūrimas**

## Projekto paruošimas ir sukonfigūravimas

Sukūrę Visual Studio projektą parsisiuntėme ir sukonfigūravome bibliotekas, skirtas darbui su OpenGL: GLFW, GLEW ir stb\_image. ![](RackMultipart20221206-1-khe6h8_html_142bfcef03ad0504.png)

_pav. 5: Išorinių bibliotekų susiejimas su projektu per Visual Studio_

Teisingai sukonfigūravus projektą pavyko sukurti tuščią programos langą:

![](RackMultipart20221206-1-khe6h8_html_3e6ddbd3fb97a6f0.png)

_pav. 6: Sukurtas tuščias programos langas_

Taip pat, naudojant bibliotekos funkcijas, nupiešti stačiakampį programos lange:

![](RackMultipart20221206-1-khe6h8_html_e5ed36592e687ca5.png)

_pav. 7: Programos lange nupiešiamas baltas stačiakampis_

## Abstrakcijų kūrimas

Net tokiam paprastam stačiakampiui, kuris pavaizduotas viršuje, nupiešti, prireikia palyginus daug operacijų: deklaruoti masyvą su 8 elementais – stačiakampio kiekvienos viršūnės X ir Y koordinatėmis, nurodyti RGB spalvą ir iškviesti 3 OpenGL bibliotekų suteiktas funkcijas. Akivaizdu, kad norint sukurti ganėtinai kompleksišką žaidimą, kaip „Tetris", reikia supaprastinti kodą, įvesti abstrakcijų. Tai yra, reikia sukurti sistemą, lyg labai primityvų žaidimų variklį, kurį sudaro, atskirų paveiksliukų objektų supaprastintas sukūrimas, automatizuotas jų piešimas ant ekrano, tekstūrų uždėjimas. Šios sistemos sukūrimas leidžia atlikti tam tikrus, gana kompleksiškus darbus, vienos funkcijos iškvietimu. Pagrindinės mūsų sukurtos abstrakcinės funkcijos:

// iš paveiksliuko padaro tekstūrą

int AddTexture(std::stringpath)

// nupiešia kvadratą

int Square(floatx, floaty, floatplotis, floatilgis, inttekstura)

// panaikina kvadratą

void SquareRemove(int square)

Šių funkcijų panaudojimo pavyzdys:

![](RackMultipart20221206-1-khe6h8_html_5172fbccfb7cf470.png) ![](RackMultipart20221206-1-khe6h8_html_dac24871b2b86dcd.png)

_pav. 8: Sukuriamas paveiksliuko objektas su katės tekstūra naudojant abstrakcines funkcijas_

## „Tetris" žaidimo logikos kūrimas

Turint viršuje paminėtas abstrakcijas, pagaliau galima pradėti kurti patį žaidimą.

Šis žaidimas – tai begalinis ciklas, kuriame atliekami tam tikri skaičiavimai, o priėjus instrukcijų galą, atnaujinamas vaizdo kadras ir programa „užmiega" 50 milisekundžių naudojant standartinę C++ bibliotekos funkciją, o tada vėl kartoja ciklą:

std::this\_thread::sleep\_for(std::chrono::milliseconds(50));

V ![](RackMultipart20221206-1-khe6h8_html_3f1ea20814df1236.png) isi skaičiavimai ir žaidimo operacijos, kaip figūros pasukimas, vyksta skaičių kintamuosiuose. Žaidimų laukas, kaladėlių esama vieta, žaidimo greitis ir kiti parametrai apibūdinantys žaidimo būseną taip pat saugomi skaičių kintamuosiuose. Svarbiausias kintamasis – grid[] skaičių masyvas, reprezentuojantis žaidimų lauką. Jo dydis priklauso nuo žaidimo lauko ilgio ir pločio, t.y. grid[ilgis\*plotis]. Kas 50 milisekundžių gavus žaidėjo klaviatūros įvestį ir atlikus skaičiavimus, gaunamas galutinis skaičių masyvas grid[], kuris yra išvedamas į ekraną (seni kvadratėliai pašalinami) naudojant viršuje paminėtas abstrakcines funkcijas.

![](RackMultipart20221206-1-khe6h8_html_cfcd0bfd4e87920b.png)

_pav. 9: Skaičių masyvas reprezentuojantis žaidimų lauką_

![Shape6](RackMultipart20221206-1-khe6h8_html_d5a49d8bdd122758.gif)

_pav. 10: Skaičių masyvas išvedamas į ekraną naudojant abstrakcines funkcijas_

Naudojant šitą techniką, galiausiai sukūrėme pirminę žaidimo versiją.

![](RackMultipart20221206-1-khe6h8_html_6ba2544434953bab.gif)

_pav. 11: Pirminė žaidimo versija_

## Scenų valdymo sistemos ir meniu kūrimas

![Shape8](RackMultipart20221206-1-khe6h8_html_4cea71c1ed31b508.gif)

_pav. 12: Skirtingos žaidimo scenos_

Žaidimui reikėjo pagrindinio meniu ir žaidimo nustatymų meniu. Meniu veikimo principas labai paprastas: nupiešiama nuotrauka su visu tekstu ir paveiksliukais bei ant pasirinkto mygtuko uždedamas tuščiaviduris stačiakampis – žymeklis. Judinant jį su klaviatūros klavišais sekama, kuris mygtukas yra pažymėtas ir ant jo perkeliamas žymeklis. Paspaudus ENTER atliekama to mygtuko funkcija. Meniu galima sutikti dar dviejų tipų elementus: slankjuostes ir kintamojo užrašo mygtukus. Pastarieji veikia paprastai: ant pradinio paveiksliuko uždedama arba pašalinama vieno žodžio tekstūra. Slankjuostės veikia kitaip: jos padaromos iškerpant plotelį pradinės tekstūros ir už jos uždedant baltą stačiakampį, kuris slankioja į vieną ar kitą pusę. Taip pat yra vienas ypatingas elementas: žaidimo lauko dydžio keitimas. Jis veikia taip: uždedamas paveiksliukas, vaizduojantis visus žaidimo lauko dydžius. Ant jo uždedamas baltas stačiakampis, vaizduojantis dabartinį pasirinktą lauko dydį, ir skaičiukai šonuose, rodantys tikslias jo reikšmes. Pagrindiniame meniu galima pasirinkti eiti į nustatymus, žaisti žaidimą ar išeiti iš programos. Nustatymuose galima išjungti/įjungti garsą, keisti jo dydį, keisti žaidimo figūrų kritimo pradinį ir maksimalų greičius, greitėjimą. Taip pat, galima keisti žaidimo lauko dydį, pašalinti taškų rekordą, pasirinkti, kad žaidimas būtų paleistas pilno ekrano režimu. Taip pat, yra žaidimo įvadas, pasirodantis paleidus žaidimą, kuris pamoko, kaip žaisti.

## Žaidimo gerinimas

Turint veikiantį meniu, beliko gerinti patį žaidimą. Visų pirma, pridėjome žaidimui muziką. Tuomet parašėme algoritmą, kuris automatiškai pakeistų visų elementų dydį ir išcentruotų žaidimų lauką, kad žaidėjas galėtų pasirinkti, kokį nori žaidimo lauko dydį, net ir 1000x1000.

![Shape10](RackMultipart20221206-1-khe6h8_html_87f91650e7ed7226.gif)

_pav. 13: Skirtingų dydžių žaidimo laukai_

Galiausiai, naudodamiesi grafikos kūrimo įrankiais padarėme geresnes žaidimo tekstūras: skirtingų spalvų kvadratėlius, žaidimų lauko linijas ir foną. Žaidimas dabar atrodo taip:

![](RackMultipart20221206-1-khe6h8_html_d576f3087498e73b.png)

_pav. 14: Pagerintos žaidimo grafikos_

## ![Shape13](RackMultipart20221206-1-khe6h8_html_e4a6c746b710bb5f.gif)

_pav. 15: Robotas Samuolis_

Autonominės programos, žaidžiančios žaidimą, kūrimas

Susipažinkite su robotu Samuoliu:

Samuolio egzistencijos tikslas – žaisti kuo geriau arba kuo blogiau žaidimą „Tetris", priklausomai nuo nuotaikos. Jo veikimo principas gana paprastas: pagal mūsų sukurtą algoritmą yra įvertinama kiekviena įmanoma pozicija, kur galima pastatyti dabar valdomą figūrą. Pasirenkama ta pozicija, kuri surenka daugiausiai (arba mažiausiai) taškų. Algoritmas skiria arba atima taškus iš pozicijos pagal tokius kriterijus:

• Kuo žemiau pastatoma figūra, tuo ėjimas geresnis.

• Kuo mažiau tarpų paliekama po figūra, tuo ėjimas geresnis.

• Kuo daugiau linijų sunaikinama pastačius figūrą, tuo ėjimas geresnis.

![](RackMultipart20221206-1-khe6h8_html_d9aa0757844e9bce.png)

_pav. 16: Į komandinę eilutę išspausdinami duomenys apie roboto pasirinktą ėjimą_

Algoritmas, naudojantis šiuos ir kitus paprastus kriterijus, sugeba žaisti vidutiniškai geriau, negu žmogus.

#


# Tobulinimo galimybės

Žaidime šiuo metu nėra kai kurių funkcijų, esančių moderniose ir profesionaliose tetrio versijose: figūros kol kas parenkamos visiškai atsitiktinai, tai sukuria situacijų, kai pralaimima tiesiog dėl atsitiktinumo. Taip pat, neįmanoma vienu metu sudėti daugiau nei keturių eilučių, kai tuo tarpu profesionaliose versijose galima ir dvidešimt. Be to, nors žaidimas atrodo neblogai, jo tekstūras būtų galima pagražinti.

# Išvados

Pavyko sukurti žaidimą be žaidimo variklio. Supratome, kad tai yra ilgas, varginantis, tačiau įdomus procesas. Kurdami žaidimą patobulėjome ir daug ko išmokome:

- Patobulinome savo programavimo ir darbo komandoje įgūdžius.
- Įgijome žinių apie kompiuterinės grafikos, abstrakcijų ir sistemų kūrimą.
- Išmokome tvarkyti ir organizuoti didelės apimties projekto struktūrą.

# Ateities Planai

Ateityje žadame neapleisti žaidimų kūrimo, kurti kitus, originalesnius žaidimus. Darydami šį projektą įgijome naudingos patirties, padėsiančios ateityje.

Šį žaidimą galima parsisiųsti iš: [https://github.com/chicken-brother/Tetris-Release](https://github.com/chicken-brother/Tetris-Release)

# Informacijos šaltiniai

1. [https://www.khronos.org/opengl/wiki/](https://www.khronos.org/opengl/wiki/)
2. [https://www.glfw.org/documentation.html](https://www.glfw.org/documentation.html)
3. [https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ\_Ev03o2oq3-GGOS2](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
4. [https://stackoverflow.com/](https://stackoverflow.com/)