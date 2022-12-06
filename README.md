PANEVĖŽIO JUOZO BALČIKONIO GIMNAZIJA Projektinis darbas

# **Žaidimo kūrimas naudojant C++ programavimo kalbą**

**Antanas Vasiliauskas IIIf**

**Augustinas Jarockis IIIe**

Vadovė Renata Burbaitė

Panevėžys

2021

# Turinys

[**Įvadas**](#_Toc73875048)

[**Darbo tikslas**](#_Toc73875049)

[**Naudojamos programos ir C++ bibliotekos**](#_Toc73875050)

[**Darbo eiga**](#_Toc73875051)

[**Projekto paruošimas ir sukonfigūravimas**](#_Toc73875052)

[**Abstrakcijų kūrimas**](#_Toc73875053)

[„ **Tetris" žaidimo logikos kūrimas**](#_Toc73875054)

[**Scenų valdymo sistemos ir meniu kūrimas**](#_Toc73875055)

[**Žaidimo gerinimas**](#_Toc73875056)

[**Autonominės programos, žaidžiančios žaidimą, kūrimas**](#_Toc73875057)

[**Tobulinimo galimybės**](#_Toc73875058)

[**Išvados**](#_Toc73875059)

[**Ateities Planai**](#_Toc73875060)

[**Informacijos šaltiniai**](#_Toc73875061)

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

![image](https://user-images.githubusercontent.com/118690121/205935726-6c292c85-c5ba-46c4-b619-0f609fd3b5b9.png)

_pav. 1: Visual Studio_

**Visual Studio 2017**

- Kodo redagavimo įrankis, kuris paryškina C++ kalbos sintaksę ir rodo klaidas.
- Palengvina programos kompiliavimo procesą, tad nereikia pačiam kompiliuoti programos per komandinę eilutę.

![image](https://user-images.githubusercontent.com/118690121/205935776-7aabcfab-c1e1-464e-b271-8a0589adcd2f.png)

_pav. 2: GitHub_

**GitHub**

- Leidžia patikimai saugoti skirtingas programos versijas vienoje vietoje.
- Leidžia vienu metu dirbti keliems žmonėms prie to pačio projekto ir vėliau sujungti pakeitimus.

![image](https://user-images.githubusercontent.com/118690121/205936043-6a03a959-2673-4b4b-a107-4221a6caffb9.png)
![image](https://user-images.githubusercontent.com/118690121/205936139-f06a9387-e91a-4bbc-a1e0-e29e390031c7.png)

**OpenGL GLEW ir GLFW C++ bibliotekos**

- Suteikia bazines funkcijas, tokias kaip tuščio programos lango sukūrimas, 2D figūrų braižymas nurodant RGB spalvą bei figūros viršūnių koordinates ir pan.
_pav. 3: Projekte naudojamos bibliotekos_
- Suteikia funkcijas, palengvinančias naudotojo klaviatūros įvesties fiksavimą.
- stb\_image biblioteka leidžianti paveiksliukus paversti tekstūromis.

![image](https://user-images.githubusercontent.com/118690121/205936191-a26927a4-2bc6-4cdb-89fc-501dc23f6728.png)

**Inkscape ir Pixlr grafikos kūrimo programos**

- ![image](https://user-images.githubusercontent.com/118690121/205936219-9a28ed7d-96f5-4421-822c-c921e0d184da.png) Suteikia įrankius, leidžiančius sukurti žaidimui naudojamus paveikslėlius.

_pav. 4: Grafikos kūrimo programų logotipai_

# Darbo eiga

Visą darbo eigą galima suskirstyti į šiuos mažesnius tikslus, kuriuos teko įvykdyti:

1. **Projekto paruošimas ir sukonfigūravimas**
2. **Abstrakcijų kūrimas**
3. **"Tetris" žaidimo logikos kūrimas**
4. **Scenų valdymo sistemos ir meniu kūrimas**
5. **Žaidimo gerinimas**
6. **Autonominės programos, žaidžiančios žaidimą, kūrimas**

## Projekto paruošimas ir sukonfigūravimas

Sukūrę Visual Studio projektą parsisiuntėme ir sukonfigūravome bibliotekas, skirtas darbui su OpenGL: GLFW, GLEW ir stb\_image. ![image](https://user-images.githubusercontent.com/118690121/205936342-01d7b51d-9562-43bd-9c2c-6354acac34eb.png)

_pav. 5: Išorinių bibliotekų susiejimas su projektu per Visual Studio_

Teisingai sukonfigūravus projektą pavyko sukurti tuščią programos langą:

![image](https://user-images.githubusercontent.com/118690121/205936391-7115ee9a-f323-4a79-9bde-e6e761d97be8.png)

_pav. 6: Sukurtas tuščias programos langas_

Taip pat, naudojant bibliotekos funkcijas, nupiešti stačiakampį programos lange:

![image](https://user-images.githubusercontent.com/118690121/205936423-ed3712f7-2892-47eb-8a9d-1f2c7817b575.png)

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

![image](https://user-images.githubusercontent.com/118690121/205936489-eaeaa7bd-f3fa-40d2-945f-5ec50ef31fc7.png)

![image](https://user-images.githubusercontent.com/118690121/205936772-d9e9177d-6b20-4d4c-82d9-fbba2392041b.png)


_pav. 8: Sukuriamas paveiksliuko objektas su katės tekstūra naudojant abstrakcines funkcijas_

## „Tetris" žaidimo logikos kūrimas

Turint viršuje paminėtas abstrakcijas, pagaliau galima pradėti kurti patį žaidimą.

Šis žaidimas – tai begalinis ciklas, kuriame atliekami tam tikri skaičiavimai, o priėjus instrukcijų galą, atnaujinamas vaizdo kadras ir programa „užmiega" 50 milisekundžių naudojant standartinę C++ bibliotekos funkciją, o tada vėl kartoja ciklą:

std::this\_thread::sleep\_for(std::chrono::milliseconds(50));

Visi skaičiavimai ir žaidimo operacijos, kaip figūros pasukimas, vyksta skaičių kintamuosiuose. Žaidimų laukas, kaladėlių esama vieta, žaidimo greitis ir kiti parametrai apibūdinantys žaidimo būseną taip pat saugomi skaičių kintamuosiuose. Svarbiausias kintamasis – grid[] skaičių masyvas, reprezentuojantis žaidimų lauką. Jo dydis priklauso nuo žaidimo lauko ilgio ir pločio, t.y. grid[ilgis\*plotis]. Kas 50 milisekundžių gavus žaidėjo klaviatūros įvestį ir atlikus skaičiavimus, gaunamas galutinis skaičių masyvas grid[], kuris yra išvedamas į ekraną (seni kvadratėliai pašalinami) naudojant viršuje paminėtas abstrakcines funkcijas.

![image](https://user-images.githubusercontent.com/118690121/205936852-219b5d93-cbb4-46df-b535-e1eb0b06db01.png)

_pav. 9: Skaičių masyvas reprezentuojantis žaidimų lauką_

![image](https://user-images.githubusercontent.com/118690121/205936931-e2b34a50-0b2c-41d2-915e-773d5790f4de.png)

![image](https://user-images.githubusercontent.com/118690121/205936916-43958728-ce63-4a2d-990c-0dd89e76553d.png)

_pav. 10: Skaičių masyvas išvedamas į ekraną naudojant abstrakcines funkcijas_

Naudojant šitą techniką, galiausiai sukūrėme pirminę žaidimo versiją.

![](RackMultipart20221206-1-khe6h8_html_6ba2544434953bab.gif)

_pav. 11: Pirminė žaidimo versija_

## Scenų valdymo sistemos ir meniu kūrimas

![Shape8](RackMultipart20221206-1-khe6h8_html_4cea71c1ed31b508.gif)

_pav. 12: Skirtingos žaidimo scenos_

Žaidimui reikėjo pagrindinio meniu ir žaidimo nustatymų meniu. Meniu veikimo principas labai paprastas: nupiešiama nuotrauka su visu tekstu ir paveiksliukais bei ant pasirinkto mygtuko uždedamas tuščiaviduris stačiakampis – žymeklis. Judinant jį su klaviatūros klavišais sekama, kuris mygtukas yra pažymėtas ir ant jo perkeliamas žymeklis. Paspaudus ENTER atliekama to mygtuko funkcija. Meniu galima sutikti dar dviejų tipų elementus: slankjuostes ir kintamojo užrašo mygtukus. Pastarieji veikia paprastai: ant pradinio paveiksliuko uždedama arba pašalinama vieno žodžio tekstūra. Slankjuostės veikia kitaip: jos padaromos iškerpant plotelį pradinės tekstūros ir už jos uždedant baltą stačiakampį, kuris slankioja į vieną ar kitą pusę. Taip pat yra vienas ypatingas elementas: žaidimo lauko dydžio keitimas. Jis veikia taip: uždedamas paveiksliukas, vaizduojantis visus žaidimo lauko dydžius. Ant jo uždedamas baltas stačiakampis, vaizduojantis dabartinį pasirinktą lauko dydį, ir skaičiukai šonuose, rodantys tikslias jo reikšmes. Pagrindiniame meniu galima pasirinkti eiti į nustatymus, žaisti žaidimą ar išeiti iš programos. Nustatymuose galima išjungti/įjungti garsą, keisti jo dydį, keisti žaidimo figūrų kritimo pradinį ir maksimalų greičius, greitėjimą. Taip pat, galima keisti žaidimo lauko dydį, pašalinti taškų rekordą, pasirinkti, kad žaidimas būtų paleistas pilno ekrano režimu. Taip pat, yra žaidimo įvadas, pasirodantis paleidus žaidimą, kuris pamoko, kaip žaisti.

![image](https://user-images.githubusercontent.com/118690121/205937034-384367b5-a9a2-41bc-9fb5-5b4910808ed2.png)


## Žaidimo gerinimas

Turint veikiantį meniu, beliko gerinti patį žaidimą. Visų pirma, pridėjome žaidimui muziką. Tuomet parašėme algoritmą, kuris automatiškai pakeistų visų elementų dydį ir išcentruotų žaidimų lauką, kad žaidėjas galėtų pasirinkti, kokį nori žaidimo lauko dydį, net ir 1000x1000.

![image](https://user-images.githubusercontent.com/118690121/205937075-dc11eab3-2087-4140-9073-e9ce5f5825d7.png)
_pav. 13: Skirtingų dydžių žaidimo laukai_

Galiausiai, naudodamiesi grafikos kūrimo įrankiais padarėme geresnes žaidimo tekstūras: skirtingų spalvų kvadratėlius, žaidimų lauko linijas ir foną. Žaidimas dabar atrodo taip:

![image](https://user-images.githubusercontent.com/118690121/205937246-3134bc09-a2bf-4935-8bfe-712b05235c82.png)

_pav. 14: Pagerintos žaidimo grafikos_

![image](https://user-images.githubusercontent.com/118690121/205937331-2c4b9fa2-4ffd-4479-bc23-5e2a1901c807.png)

_pav. 15: Robotas Samuolis_

Autonominės programos, žaidžiančios žaidimą, kūrimas

Susipažinkite su robotu Samuoliu:

Samuolio egzistencijos tikslas – žaisti kuo geriau arba kuo blogiau žaidimą „Tetris", priklausomai nuo nuotaikos. Jo veikimo principas gana paprastas: pagal mūsų sukurtą algoritmą yra įvertinama kiekviena įmanoma pozicija, kur galima pastatyti dabar valdomą figūrą. Pasirenkama ta pozicija, kuri surenka daugiausiai (arba mažiausiai) taškų. Algoritmas skiria arba atima taškus iš pozicijos pagal tokius kriterijus:

• Kuo žemiau pastatoma figūra, tuo ėjimas geresnis.

• Kuo mažiau tarpų paliekama po figūra, tuo ėjimas geresnis.

• Kuo daugiau linijų sunaikinama pastačius figūrą, tuo ėjimas geresnis.

![image](https://user-images.githubusercontent.com/118690121/205937384-1b08bd6a-3f6a-4a26-bdfc-210fb635891e.png)

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
