#include "TetrisGame.h"


/*
	Vis tiek pralaimi. Dar būtu galima pridėti:
	Rekursija kaip ir negalima (tikrinti kiekvieno plano, po to einančios figūros (7 skirtingi variantai) visas imanomas pozicijas ir imti geriausių vidurkį)
	kiek bandžiau, paleidus šitą funkciją 10 kartų iš eilės atsiranda šioks toks strigimas, ją paleidus 100 kartų iš eilės atsiranda pastebimas
	apie 1-2s strigimas. Rekursijai 10x20 grid reikėtų 4*10*7 = 280 funkcijų iškvietimų. Nebent reikėtų šitą funkciją nukelti į background thread
	ir nejudinti roboto kol jis skaičiuoja.

	Lygumo koeficientą, pagal tai, kiek skiriasi šalia esančios x ašyje aukščiausios kaladėlių vietos


	---(Netinka arba reikia kitaip sukonfiguruoti score nes, labai pablogina performance - stato bokštelius 2-3 pločio iki viršaus
		kadangi stengiasi išvengti gilinti tarpus)
	 Kažkaip paskatinti robotą naikinti jau esamus tarpus (ne tik nekurti naujų) 
	---

	Dažniausiai visas problemas sukelia violetinės figūros, nes robotas nemoka apeiti iš šonų, ir jos labai dažnai palieką tarpą.
	Gal rekursinę funkciją tik joms? Arba sukurti kokią kitą funkciją, kad duotu scoro, jeigu paliekama tokia grid, kad galima pastatyti
	violetinės figūras be tarpų.
*/

void TetrisGame::CalculatePlanScore(Plan &plan, std::vector<int> plan_grid) {

	int lines_count = 0;
	int actual_y = 0;
	int spaces_created = 0;

	int total_spaces = 0;
	int total_spaces_depth = 0;
	

	// ============================== Pataiso grid'ą, jei neteisingas.
	std::vector<int> plan_lines;

	for (int py = 0; py < grid_height; py++) {

		bool bLine = true;
		for (int px = 0; px < grid_width; px++) {
			if (plan_grid[(py)* grid_width + px] == 0) {
				bLine = false;
				break;
			}
		}
		if (bLine) {
			for (int px = 0; px < grid_width; px++)
				plan_grid[(py)* grid_width + px] = 0;

			plan_lines.push_back(py);
		}
	}

	for (auto &v : plan_lines)
		for (int px = 0; px < grid_width; px++)
		{
			for (int py = v; py > 0; py--)
				plan_grid[py * grid_width + px] = plan_grid[(py - 1) * grid_width + px];
			plan_grid[px] = 0;
		}
	plan_lines.clear();

	// =============================== Išmeta neįmanomas pozicijas
	if (!DoesPieceFit(currentPiece, plan.rotation, plan.xposition, 0, plan_grid)) {
		plan.score = -100000;
		return;
	}


	
	// ============================== Apskaičiuoja best_y kuris naudojamas kituose skaičiavimuose (best_y != actual_y)
	int best_y = 0;
	for (int y = 1; y < grid_height; y++) {
		if (DoesPieceFit(currentPiece, plan.rotation, plan.xposition, y, plan_grid)) {
			best_y++;
		}
	}

	// ============================== Įpiešią figūros poziciją, į grid'o kopiją.

	for (int px = 0; px < 4; px++) {
		for (int py = 0; py < 4; py++) {
			if (shape[currentPiece][Rotate(px, py, plan.rotation)] != 0) {
				plan_grid[(px + plan.xposition) + (py + best_y)*grid_width] = -2;
			}
		}
	}

	// ============================== Jei grid'o kopija turi linijų, jas sunaikina

	for (int py = 0; py < 4; py++)
		if (best_y + py < grid_height) {
			bool bLine = true;
			for (int px = 0; px < grid_width; px++) {
				if (plan_grid[(best_y + py) * grid_width + px] == 0) {
					bLine = false;
					break;
				}
			}
			if (bLine) {
				for (int px = 0; px < grid_width; px++)
					plan_grid[(best_y + py) * grid_width + px] = 0;

				plan_lines.push_back(best_y + py);
				// ==========================================================================================
				lines_count++;
				// ==========================================================================================
			}
		}
		
	for (auto &v : plan_lines)
		for (int px = 0; px < grid_width; px++)
		{
			for (int py = v; py > 0; py--)
				plan_grid[py * grid_width + px] = plan_grid[(py - 1) * grid_width + px];
			plan_grid[px] = 0;
		}
		
	// ============================== Apskaičiuoja Y nuo grid apačios
	for (int y = grid_height - 1; y >= 0; y--) {
		for (int x = grid_width - 1; x >= 0; x--) {
			if (plan_grid[y*grid_width + x] == -2) {
				// ==========================================================================================
				if (actual_y < grid_height - y) actual_y = grid_height - y;
				// ==========================================================================================
			}
		}
	}
		


	// ============================== Suskaičiuoja naujų tarpų skaičių

	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			if (plan_grid[i * grid_width + j] == -2) {
				for (int k = 1; (i + k) * grid_width + j < grid_width * grid_height; k++) {
					//==========================================================================================
					if (plan_grid[(i + k)*grid_width + j] == 0) spaces_created++;
					//==========================================================================================
					else break;

				}
			}
		}
	}

	// ============================== Suskaičiuoja visus tarpus ir jų gylį

	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			if (plan_grid[i * grid_width + j] == 0) {
				bool already = false;
				for (int k = 1; (i - k) * grid_width + j > 0; k++) {
					//==========================================================================================
					if (plan_grid[(i - k)*grid_width + j] != 0) {
						if (!already) {
							total_spaces++;
							already = true;
						} 
						total_spaces_depth++;
					} 
					//==========================================================================================
				}
			}
		}
	}
	
	// ============================== Apskaičiuoja Score
		
	plan.score -= 1000 * sqrt(spaces_created);
	int coefficient = 400 * actual_y *(float)actual_y / (float)grid_height; // Kuo aukščiau, tuo DIDESNĖ nuobauda, kitaip pradeda statyti bokštelius iki viršaus
	plan.score -= coefficient;  
	plan.score += lines_count * 400;

	// Kuo aukščiau tuo MAŽESNĖ nuobauda, kitaip pradeda statyti bokštelius iki viršaus
	int spaces_coefficient = total_spaces_depth * 0.5 * (float)grid_height / (float)actual_y + total_spaces_depth * 5 * (float)grid_height / (float)actual_y;  
	
	// LABAI PABLOGINA PERFORMANCE
	//plan.score -= spaces_coefficient;

	
	// ============================== Išspausdina info
	/*
	if (plan.score > bestPlan.score) {
		std::cout << "======== score:" << plan.score << " spaces: " << spaces_created << " actual_y&coef: " << actual_y << "&" << coefficient <<" lines: " << lines_count << std::endl;
		std::cout << "======== total_spaces:" << total_spaces << " total_spaces_depth: " << total_spaces_depth << " coef: " << spaces_coefficient << std::endl;
		for (int i = 0; i < grid_height; i++) {
			for (int j = 0; j < grid_width; j++) {
				if (plan_grid[i * grid_width + j] == -2) {
					std::cout << "[]";
				}
				else if (plan_grid[i * grid_width + j] == -1) {
					std::cout << "- ";
				}
				else if (plan_grid[i * grid_width + j] == 0) {
					std::cout << ". ";
				}
				else {
					std::cout << plan_grid[i * grid_width + j] << " ";
				}

			}
			std::cout << std::endl;
		}
	}
	*/




		
		
}

void TetrisGame::GameLoop(int Inputs[], GLFWwindow* window)
{
	if (buvo == false)
	{
		Texture loading_texture("Textures/tetris_loading_screen.png");
		loading_texture.Bind();
		_Square loading_pic(0, 0, 1, 1, 0);
		loading_pic._Draw(shaderis, rendereris);
		glfwSwapBuffers(window);
		background_texture = AddTexture("Textures/background.png");
		tekstura9 = AddTexture("Textures/White.png");
		boom_texture = AddTexture("Textures/boom.png");
		border_texture_vertical = AddTexture("Textures/neon_line_vertical.png");
		border_texture_horizontal = AddTexture("Textures/neon_line_horizontal.png");
		tetris_block_texture_1 = AddTexture("Textures/tetris_block_1.png");
		tetris_block_texture_2 = AddTexture("Textures/tetris_block_2.png");
		tetris_block_texture_3 = AddTexture("Textures/tetris_block_3.png");
		tetris_block_texture_4 = AddTexture("Textures/tetris_block_4.png");
		tetris_block_texture_5 = AddTexture("Textures/tetris_block_5.png");
		tetris_block_texture_6 = AddTexture("Textures/tetris_block_6.png");
		tekstura3 = AddTexture("Textures/Score.png");
		tekstura4 = AddTexture("Textures/Game over 2.png");


		grid_element_texture = AddTexture("Textures/grid_element.png");
		
		tekstura13 = AddTexture("Textures/Gameplay settings.png");
		tekstura10 = AddTexture("Textures/Audio settings.png");
		tekstura14 = AddTexture("Textures/Grid size select lentele.png");


		for (int i = 0; i < 10; i++)
		{
			char numeris = i + 48;
			std::string kelias = "Textures/";
			kelias += numeris;
			kelias += ".png";
			SkaiciuTeksturos[i] = AddTexture(kelias);
		}
		for (int i = 0; i < 3; i++)
		{
			char numeris = i + 49;
			std::string kelias = "Textures/Robotas";
			kelias += numeris;
			kelias += ".png";
			RobotoTeksturos[i] = AddTexture(kelias);
		}
		tekstura6 = AddTexture("Textures/Exit lenta.png");
		tekstura7 = AddTexture("Textures/Menu Screen.png");
		tekstura11 = AddTexture("Textures/Tutorial.png");
		tekstura8 = AddTexture("Textures/Settings.png");
		tekstura12 = AddTexture("Textures/Off.png");
		tekstura5 = AddTexture("Textures/Remelis.png");

		tekstura9p = AddTexture("Textures/White.png");

		std::ifstream fd("Data/Highscore.txt");
		fd >> highscore;
		fd.close();

		std::ifstream fd2("Data/Settings.txt");
		fd2 >> MusicOn >> volume >> speedLimit >>
			startingticksToForceDown >> piecesToIncreaseSpeed
			>> grid_height >> grid_width >> MaximiseOnStart >> TutorialEnabled;
		fd2.close();
		if (MaximiseOnStart == true)
		{
			int count;
			const GLFWvidmode *mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode[count - 1].height, mode[count - 1].width, mode[count - 1].refreshRate);
			int winwidth, winheight;
			glfwGetWindowSize(window, &winwidth, &winheight);
			glViewport((winwidth - winheight) / 2, 0, winheight, winheight);
		}
		if (TutorialEnabled == true)
		{
			TutorialLentele = Square(0, 0, 0.9, 0.9, tekstura11);
		}
		buvo = true;
		
	}

	if (Scena == GameplaySettings)
	{
		if (SceneInitialized == false)
		{
			Fonas = Square(0, 0, 1, 1, tekstura13);
			Remelis = Square(0, 0.47, 0.07, 0.3, tekstura5);
			Slankjuoste = Square(-(double)((speedLimit - 2) / 58.0), 0.2, 0.05, 0.5, tekstura9);
			Slankjuoste2 = Square(-((double)((startingticksToForceDown - 2) / 58.0)), -0.1, 0.05, 0.5, tekstura9);
			Slankjuoste3 = Square(-((double)((piecesToIncreaseSpeed - 1) / 9.0)), -0.35, 0.05, 0.5, tekstura9);
			SceneInitialized = true;
			mygtukas = 0;
			buttonBlocked = true;
		}
		if (buttonBlocked == true)
			if (!(Key_Enter || Key_Up || Key_Down || Key_W || Key_S))
				buttonBlocked = false;
		if (mygtukas == 0)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				speedLimit = 5;
				startingticksToForceDown = 20;
				piecesToIncreaseSpeed = 3;
				MoveA(Slankjuoste, -(double)((speedLimit - 2) / 58.0), 0.2);
				MoveA(Slankjuoste2, -((double)((startingticksToForceDown - 2) / 58.0)), -0.1);
				MoveA(Slankjuoste3, -((double)((piecesToIncreaseSpeed - 1) / 9.0)), -0.35);
				grid_height = 20;
				grid_width = 10;

				buttonBlocked = true;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.72);
				mygtukas = 5;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.295);
				mygtukas = 1;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 1)
		{
			if ((Key_A == GLFW_PRESS || Key_Left == GLFW_PRESS) && speedLimit < 60 && DeltaTime(15))
			{
				if (speedLimit < startingticksToForceDown)
				{
					speedLimit++;
					MoveA(Slankjuoste, -((double)((speedLimit - 2) / 58.0)), 0.2);
				}
				else
				{
					speedLimit++;
					startingticksToForceDown = speedLimit;
					MoveA(Slankjuoste, -((double)((speedLimit - 2) / 58.0)), 0.2);
					MoveA(Slankjuoste2, -((double)((startingticksToForceDown - 2) / 58.0)), -0.1);
				}
			}
			else if ((Key_D == GLFW_PRESS || Key_Right == GLFW_PRESS) && speedLimit > 2 && DeltaTime(15))
			{
				speedLimit--;
				MoveA(Slankjuoste, -((double)((speedLimit - 2) / 58.0)), 0.2);
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.042);
				mygtukas = 2;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 2)
		{
			if ((Key_A == GLFW_PRESS || Key_Left == GLFW_PRESS) && startingticksToForceDown < 60 && DeltaTime(15))
			{
				startingticksToForceDown++;
				MoveA(Slankjuoste2, -((double)((startingticksToForceDown - 2) / 58.0)), -0.1);
			}
			else if ((Key_D == GLFW_PRESS || Key_Right == GLFW_PRESS) && startingticksToForceDown > 2 && DeltaTime(15))
			{
				if (speedLimit < startingticksToForceDown)
				{
					startingticksToForceDown--;
					MoveA(Slankjuoste2, -((double)((startingticksToForceDown - 2) / 58.0)), -0.1);
				}
				else
				{
					startingticksToForceDown--;
					speedLimit = startingticksToForceDown;
					MoveA(Slankjuoste, -((double)((speedLimit - 2) / 58.0)), 0.2);
					MoveA(Slankjuoste2, -((double)((startingticksToForceDown - 2) / 58.0)), -0.1);
				}
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.295);
				mygtukas = 1;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.22);
				mygtukas = 3;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 3)
		{
			if ((Key_A == GLFW_PRESS || Key_Left == GLFW_PRESS) && piecesToIncreaseSpeed < 10 && DeltaTime(50))
			{
				piecesToIncreaseSpeed++;
				MoveA(Slankjuoste3, -((double)((piecesToIncreaseSpeed - 1) / 9.0)), -0.35);
			}
			else if ((Key_D == GLFW_PRESS || Key_Right == GLFW_PRESS) && piecesToIncreaseSpeed > 1 && DeltaTime(50))
			{
				piecesToIncreaseSpeed --;
				MoveA(Slankjuoste3, -((double)((piecesToIncreaseSpeed - 1) / 9.0)), -0.35);
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.042);
				mygtukas = 2;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.51);
				mygtukas = 4;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 4)
		{
			if (GridLentele == true)
			{
				if ((Key_Enter == GLFW_PRESS || Key_Exit == GLFW_PRESS) && buttonBlocked == false && DeltaTime(15))
				{
					GridLentele = false;
					buttonBlocked = true;
					SquareRemove(GridSizeLentele);
					SquareRemove(Uzpildas);
					UndisplayNumber(skaiciai);
					UndisplayNumber(skaiciai2);
					Remelis = Square(0, -0.51, 0.07, 0.3, tekstura5);
				}
				else if ((Key_A == GLFW_PRESS || Key_Left == GLFW_PRESS) && grid_width > 8 && DeltaTime(15))
				{
					grid_width--;
					for (int i = 0; i < grid_height; i++)
						if (!(grid.size() == 0))
						grid.pop_back();
					SquareRemove(Uzpildas);
					Uzpildas = Square(-0.721 + (double)(grid_width / 89.0), 0.721 - (double)(grid_height / 89.0), (double)(grid_height / 89.0), (double)(grid_width / 89.0), tekstura9p);
					DisplayNumber(0, -0.85, 0.9, grid_width, skaiciai2);
				}
				else if ((Key_D == GLFW_PRESS || Key_Right == GLFW_PRESS) && grid_width < 64 && DeltaTime(15))
				{
					grid_width++;
					for (int i = 0; i < grid_height; i++)
						grid.push_back(0);
					SquareRemove(Uzpildas);
					Uzpildas = Square(-0.721 + (double)(grid_width / 89.0), 0.721 - (double)(grid_height / 89.0), (double)(grid_height / 89.0), (double)(grid_width / 89.0), tekstura9p);
					DisplayNumber(0, -0.85, 0.9, grid_width, skaiciai2);
				}
				else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && grid_height > 8 && DeltaTime(15))
				{
					grid_height--;
					if (!(grid.size() == 0))
					grid.pop_back();
					SquareRemove(Uzpildas);
					Uzpildas = Square(-0.721 + (double)(grid_width / 89.0), 0.721 - (double)(grid_height / 89.0), (double)(grid_height / 89.0), (double)(grid_width / 89.0), tekstura9p);
					DisplayNumber(0.85, 0.1, 0.9, grid_height, skaiciai);
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && grid_height < 64 && DeltaTime(15))
				{
					grid_height++;
					grid.push_back(0);
					SquareRemove(Uzpildas);
					Uzpildas = Square(-0.721 + (double)(grid_width / 89.0), 0.721 - (double)(grid_height / 89.0), (double)(grid_height / 89.0), (double)(grid_width / 89.0), tekstura9p);
					DisplayNumber(0.85, 0.1, 0.9, grid_height, skaiciai);
				}
			}
			else
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					GridSizeLentele = Square(0, 0, 1, 1, tekstura14);
					DisplayNumber(0.85, 0.1, 0.9, grid_height, skaiciai);
					DisplayNumber(0, -0.85, 0.9, grid_width, skaiciai2);
					Uzpildas = Square(-0.721 + (double)(grid_width / 89.0), 0.721 - (double)(grid_height / 89.0), (double)(grid_height / 89.0), (double)(grid_width / 89.0), tekstura9p);
					SquareRemove(Remelis);
					GridLentele = true;
					buttonBlocked = true;
				}
				else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.22);
					mygtukas = 3;
					buttonBlocked = true;
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.72);
					mygtukas = 5;
					buttonBlocked = true;
				}
			}
		}
		if (mygtukas == 5)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				UnloadScene();
				Scena = Settings; //Go to settings
				SceneInitialized = false;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.51);
				mygtukas = 4;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
		}
	}

	if (Scena == AudioSettings)
	{
		if (SceneInitialized == false)
		{
			Fonas = Square(0, 0, 1, 1, tekstura10);
			Remelis = Square(0, 0.47, 0.07, 0.3, tekstura5);
			Slankjuoste = Square(-1.0 + ((double)(volume/100.0)), 0, 0.05, 0.5, tekstura9);
			SceneInitialized = true;
			mygtukas = 0;
			buttonBlocked = true;
			if (MusicOn == false) Off = Square(0.1, 0.32, 0.05, 0.05, tekstura12);
		}
		if (buttonBlocked == true)
			if (!(Key_Enter || Key_Up || Key_Down || Key_W || Key_S))
				buttonBlocked = false;
		if (mygtukas == 0)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				Muzika._ChangeVolume(100);
				volume = 100;
				MoveA(Slankjuoste, 0, 0);
				if (MusicOn == false) SquareRemove(Off);
				MusicOn = true;
				
				buttonBlocked = true;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.72);
				mygtukas = 3;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.32);
				mygtukas = 1;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 1)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				buttonBlocked = true;
				if (MusicOn == true)
				{
					MusicOn = false;
					Off = Square(0.1, 0.32, 0.05, 0.05, tekstura12);
					MoveA(Remelis, 0, 0.32); //Reiktu issiaiskinti, kodel funkcija virsuj perkelia zymekli blogon vieton 
				}
				else
				{
					MusicOn = true;
					SquareRemove(Off);
				}
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.175);
				mygtukas = 2;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 2)
		{
			if ((Key_A == GLFW_PRESS || Key_Left == GLFW_PRESS) && volume > 0 && DeltaTime(10))
			{
				volume--;
				MoveA(Slankjuoste, -1.0 + ((double)(volume / 100.0)), 0);
				Muzika._ChangeVolume(volume);
			}
			else if ((Key_D == GLFW_PRESS || Key_Right == GLFW_PRESS) && volume < 100 && DeltaTime(10))
			{
				volume++;
				MoveA(Slankjuoste, -1.0 + ((double)(volume / 100.0)), 0);
				Muzika._ChangeVolume(volume);
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.32);
				mygtukas = 1;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.72);
				mygtukas = 3;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 3)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				UnloadScene();
				Scena = Settings; //Go to settings
				SceneInitialized = false;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.175);
				mygtukas = 2;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
		}
	}

	if (Scena == Settings)
	{
		if (SceneInitialized == false)
		{
			Fonas = Square(0, 0, 1, 1, tekstura8);
			Remelis = Square(0, 0.47, 0.07, 0.4, tekstura5);
			SceneInitialized = true;
			mygtukas = 0;
			buttonBlocked = true;
			if (MaximiseOnStart == false) Off = Square(0.29, -0.003, 0.05, 0.05, tekstura12);
		}
		if (buttonBlocked == true)
			if (!(Key_Enter || Key_Up || Key_Down || Key_W || Key_S))
				buttonBlocked = false;
		if (mygtukas == 0)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				std::ofstream fr("Data/Highscore.txt");
				fr << 0 << std::endl;
				fr.close();
				highscore = 0;
				buttonBlocked = true;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.72);
				mygtukas = 4;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.32);
				mygtukas = 1;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 1)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				UnloadScene();
				Scena = AudioSettings; //Go to audio settings
				SceneInitialized = false;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.15);
				mygtukas = 2;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 2)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				UnloadScene();
				Scena = GameplaySettings; //Go to gameplay settings
				SceneInitialized = false;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.32);
				mygtukas = 1;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.01);
				mygtukas = 3;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 3)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				if (MaximiseOnStart == false)
				{
					MaximiseOnStart = true;
					SquareRemove(Off);
				}
				else
				{
					MaximiseOnStart = false;
					Off = Square(0.29, -0.003, 0.05, 0.05, tekstura12);
					MoveA(Remelis, 0, -0.01);//Annoying
				}
				buttonBlocked = true;
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.15);
				mygtukas = 2;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.72);
				mygtukas = 4;
				buttonBlocked = true;
			}
		}
		if (mygtukas == 4)
		{
			if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
			{
				UnloadScene();
				Scena = Menu; //Go to menu
				SceneInitialized = false;
				std::ofstream fr("Data/Settings.txt");
				fr << MusicOn << " " << volume << " " << speedLimit <<
					" " << startingticksToForceDown << " " << piecesToIncreaseSpeed
					<< " " << grid_height << " " << grid_width << " " << MaximiseOnStart << " " << TutorialEnabled;
				fr.close();
			}
			else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, -0.01);
				mygtukas = 3;
				buttonBlocked = true;
			}
			else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
			{
				MoveA(Remelis, 0, 0.47);
				mygtukas = 0;
				buttonBlocked = true;
			}
		}
	}

	if (Scena == Menu)
	{
		if (SceneInitialized == false)
		{
			Fonas = Square(0, 0, 1, 1, tekstura7);
			if (Tutorial_Exited == false && TutorialEnabled == true)
			{
				Remelis = Square(0, -0.57, 0.055, 0.35, tekstura5);
			}
			else
			{
				Remelis = Square(0, 0.37, 0.15, 0.75, tekstura5);
			}
			SceneInitialized = true;
			mygtukas = 0;
			buttonBlocked = true;
		}
		if (buttonBlocked == true)
			if (!(Key_Enter || Key_Up || Key_Down || Key_W || Key_S))
				buttonBlocked = false;
		if (TutorialEnabled == true && Tutorial_Exited == false)
		{
			if (mygtukas == 0)
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					SquareRemove(TutorialLentele);
					buttonBlocked = true;
					Tutorial_Exited = true;
					SquareRemove(Remelis);
					Remelis = Square(0, 0.37, 0.15, 0.75, tekstura5);
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS || Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.71);
					mygtukas = 1;
					buttonBlocked = true;
				}
			}
			else if (mygtukas == 1)
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					SquareRemove(TutorialLentele);
					buttonBlocked = true;
					Tutorial_Exited = true;
					SquareRemove(Remelis);
					Remelis = Square(0, 0.37, 0.15, 0.75, tekstura5);
					TutorialEnabled = false;
					std::ofstream fr("Data/Settings.txt");
					fr << MusicOn << " " << volume << " " << speedLimit <<
						" " << startingticksToForceDown << " " << piecesToIncreaseSpeed
						<< " " << grid_height << " " << grid_width << " " << MaximiseOnStart << " " << TutorialEnabled;
					fr.close();
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS || Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.57);
					mygtukas = 0;
					buttonBlocked = true;
				}
			}
		}
		else
		{
			if (mygtukas == 0)
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					UnloadScene();
					Scena = Game; //Go to game
					SceneInitialized = false;
				}
				else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.44);
					mygtukas = 2;
					buttonBlocked = true;
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.01);
					mygtukas = 1;
					buttonBlocked = true;
				}
			}
			else if (mygtukas == 1)
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					UnloadScene();
					Scena = Settings; //Go to settings
					SceneInitialized = false;
				}
				else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, 0.37);
					mygtukas = 0;
					buttonBlocked = true;
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.44);
					mygtukas = 2;
					buttonBlocked = true;
				}
			}
			else if (mygtukas == 2)
			{
				if (Key_Enter == GLFW_PRESS && buttonBlocked == false)
				{
					std::ofstream fr("Data/Highscore.txt");
					fr << highscore << std::endl;
					fr.close();
					exit(0);
				}
				else if ((Key_Up == GLFW_PRESS || Key_W == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, -0.01);
					mygtukas = 1;
					buttonBlocked = true;
				}
				else if ((Key_Down == GLFW_PRESS || Key_S == GLFW_PRESS) && buttonBlocked == false)
				{
					MoveA(Remelis, 0, 0.37);
					mygtukas = 0;
					buttonBlocked = true;
				}
			}
		}
	}

	if (Scena == Game)
	{
		
		if (SceneInitialized == false)
		{
			modas = 1;
			int background = Square(0, 0, 1, 1.5, background_texture);
			Robotas = Square(-0.67, 0.75, 0.2, 0.3, RobotoTeksturos[modas - 1]);
			if (MusicOn == true)
			{
				Muzika._PlaySound(-1);
			}
			cell_size = pixel * 40.0f;
			margin_vertical = pixel * 50.0f;
			margin_horizontal = pixel * 50.0f;

			if ((SCREEN_WIDTH * pixel - (margin_horizontal * 2)) / grid_width > (SCREEN_HEIGHT * pixel - (margin_vertical * 2)) / grid_height) {
				cell_size = (SCREEN_HEIGHT * pixel - (margin_vertical * 2)) / grid_height;
				margin_horizontal = (SCREEN_WIDTH * pixel - cell_size * grid_width) / 2;

			}
			else {
				cell_size = (SCREEN_WIDTH * pixel - (margin_horizontal * 2)) / grid_width;
				margin_vertical = (SCREEN_HEIGHT * pixel - cell_size * grid_height) / 2;
			}

			// Draw border
			// Vertical Lines
			Square(-1 + margin_horizontal, 0, 1 - margin_vertical, pixel * 10, border_texture_vertical);
			Square(1 - margin_horizontal, 0, 1 - margin_vertical, pixel * 10, border_texture_vertical);

			//Horizontal lines
			Square(0, -1 + margin_vertical,pixel * 10, 1 - margin_horizontal, border_texture_horizontal);
			Square(0, 1 - margin_vertical,pixel * 10, 1 - margin_horizontal, border_texture_horizontal);


			currentPiece = rand() % 7;
			currentRotation = rand() % 4;
			currentX = grid_width / 2;
			currentY = 0;

			ticksToForceDown = startingticksToForceDown;

			forceDown = false;
			pieceCount = 0;
			score = 0;

			pause_a_bit = false;
			is_game_over = false;
			lines.clear();
			linesIndexes.clear();
			

			skaiciai.clear();
			is_game_over = false;

			grid.clear();

			

			square_indexes.clear();
			
			for (int i = 0; i < grid_height * grid_width; i++)
			{
				grid.push_back(0);
				square_indexes.push_back(0);
			}
			if (modas != 1)
			{
				bestPlan.score = -10000;
				// CALCULATE BEST MOVE
				for (int r = 0; r < 4; r++) {
					for (int x = -3; x < grid_width + 3; x++) {
						Plan plan = Plan(x, r);
						CalculatePlanScore(plan, grid);
						if (modas == 2)
						{
							if (bestPlan.score < plan.score) bestPlan = plan;
						}
						else if (modas == 3)
						{
							if (bestPlan.score > plan.score && plan.score > -100000) bestPlan = plan;
						}
					}
				}
			}
			
			Score = Square(0.9f, 0.9f, 0.05f, 0.075f, tekstura3);
			DisplayScore(0);
			SceneInitialized = true;
			buttonBlocked = true;
		}
		if (buttonBlocked == true)
			if (!(Key_Sound) && !(Key_Space))
				buttonBlocked = false;
		if (Key_Sound == GLFW_PRESS && buttonBlocked == false && MusicOn == true)
		{
			Muzika._ChangeSound();
			buttonBlocked = true;
		}
		if (Key_Space == GLFW_PRESS && buttonBlocked == false)
		{
			modas++;
			if (modas > 3) modas = 1;
			if (modas != 1)
			{
				bestPlan.score = -10000;
				// CALCULATE BEST MOVE
				for (int r = 0; r < 4; r++) {
					for (int x = -3; x < grid_width + 3; x++) {
						Plan plan = Plan(x, r);
						CalculatePlanScore(plan, grid);
						if (modas == 2)
						{
							if (bestPlan.score < plan.score) bestPlan = plan;
						}
						else if (modas == 3)
						{
							if (bestPlan.score > plan.score && plan.score > -100000) bestPlan = plan;
						}
					}
				}
			}
			SquareRemove(Robotas);
			Robotas = Square(-0.67, 0.75, 0.2, 0.3, RobotoTeksturos[modas - 1]);
			buttonBlocked = true;
		}
		if(MusicOn == true)
		Muzika._CheckSound();
		if (Key_Exit == GLFW_PRESS && IseitiLentele == false)
		{
			IseitiLentele = true;
		}
		//ESC mygtuko funkcija
		if (IseitiLentele == true)
		{
			if (IsejimoLenta == NULL)
			{
				IsejimoLenta = Square(0, 0, 0.4f, 0.5f, tekstura6);
				Remelis = Square(-0.22f, -0.175f, 0.12f, 0.15f, tekstura5);
			}
			if ((Key_Left == GLFW_PRESS || Key_A == GLFW_PRESS) && YraKairej == false)
			{
				MoveA(Remelis, -0.22f, -0.175f);
				YraKairej = true;
			}
			else if ((Key_Right == GLFW_PRESS || Key_D == GLFW_PRESS) && YraKairej == true)
			{
				MoveA(Remelis, 0.22f, -0.175f);
				YraKairej = false;
			}
			if (YraKairej == false && Key_Enter == GLFW_PRESS)
			{
				SquareRemove(IsejimoLenta);
				SquareRemove(Remelis);
				IseitiLentele = false;
				YraKairej = true;
				IsejimoLenta = 0;
			}
			else if (YraKairej == true && Key_Enter == GLFW_PRESS)
			{
				highscore = max(highscore, score);
				UndisplayNumber(skaiciai);
				UnloadScene();
				Scena = Menu; //Go to menu
				SceneInitialized = false;
				IseitiLentele = false;
				IsejimoLenta = NULL;
				Muzika._StopSound();
			}
		}
		else
		{
			if (!is_game_over) {
				

				// When Line is formed pause game and then clean the line
				if (pause_a_bit) {
					pause_a_bit = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(time_to_pause));
					for (int i = 0; i < linesIndexes.size(); i++) {
						SquareRemove(linesIndexes[i]);
					}
					linesIndexes.clear();
				}

				//  ================================================== TIMING ==================================================
				std::this_thread::sleep_for(std::chrono::milliseconds(tick));
				ticksPassed++;
				if (ticksPassed >= ticksToForceDown) {
					forceDown = true;
					ticksPassed = 0;
				}
				else forceDown = false;
				//  ================================================== TIMING ==================================================


				//  ================================================== INPUT ==================================================

				// Gets keys that are pressed
				for (int k = 0; k < 4; k++) {
					pressed_keys[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
				}

				if (modas != 1)
				{
					if (bestPlan.rotation != currentRotation) {
						pressed_keys[3] = true;
						bRotateHold = true;
					}

					else {
						if (bestPlan.xposition > currentX) {
							pressed_keys[0] = true;
						}
						if (bestPlan.xposition < currentX) {
							pressed_keys[1] = true;
						}
					}

					

				
					if (bestPlan.xposition == currentX && bestPlan.rotation == currentRotation) {
						pressed_keys[2] = true;
					}
				}
				

				//std::cout << currentX << " " << currentRotation << " | Plan: " << bestPlan.xposition << " " << bestPlan.rotation << std::endl;

				// If pressed -> and piece can move to the right, change the position of x to x + 1
				currentX += (pressed_keys[0] && DoesPieceFit(currentPiece, currentRotation, currentX + 1, currentY, grid)) ? 1 : 0;
				// If pressed <- and piece can move to the left, change the position of x to x - 1
				currentX -= (pressed_keys[1] && DoesPieceFit(currentPiece, currentRotation, currentX - 1, currentY, grid)) ? 1 : 0;
				// If pressed v and piece can move to the bottom , change the position of y to y + 1
				currentY += (pressed_keys[2] && DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1,grid)) ? 1 : 0;
				// If pressed Z and piece fits when rotated, change rotation
				// bRotateHold prevents piece wildly rotating when Z key is held down. 1 hold = 1 rotation
				if (pressed_keys[3])
				{
					currentRotation += (bRotateHold && DoesPieceFit(currentPiece, currentRotation + 1, currentX, currentY, grid)) ? 1 : 0;
					
					bRotateHold = false;
					if (currentRotation > 3) currentRotation = 0;
				}
				else
					bRotateHold = true;
				//  ================================================== INPUT ==================================================


				if (forceDown) {
					if (DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1, grid)) {
						currentY++;
					}
					else {
						
						// Lock the current piece in the grid
						for (int px = 0; px < 4; px++)
							for (int py = 0; py < 4; py++)
								if (shape[currentPiece][Rotate(px, py, currentRotation)] != 0)
									grid[(currentY + py)*grid_width + (currentX + px)] = shape[currentPiece][Rotate(px, py, currentRotation)];

						// Increase speed
						pieceCount++;
						if (pieceCount % piecesToIncreaseSpeed == 0)
							if (ticksToForceDown >= speedLimit) ticksToForceDown--;



						currentPiece = rand() % 7;


						// Perkėliau čia, nes kitaip meta neteisingą grid'ą robotui. 
						if (modas != 1)
						{
							bestPlan.score = -10000;
							// CALCULATE BEST MOVE
							for (int r = 0; r < 4; r++) {
								for (int x = -3; x < grid_width + 3; x++) {
									Plan plan = Plan(x, r);
									CalculatePlanScore(plan, grid);
									if (modas == 2)
									{
										if (bestPlan.score < plan.score) bestPlan = plan;
									}
									else if (modas == 3)
									{
										if (bestPlan.score > plan.score && plan.score > -100000) bestPlan = plan;
									}
								}
							}
						}

						
						// Check have got any lines and remove them
						for (int py = 0; py < 4; py++)
							if (currentY + py < grid_height) {
								bool bLine = true;
								for (int px = 0; px < grid_width; px++) {
									if (grid[(currentY + py)* grid_width + px] == 0) {
										bLine = false;
										break;
									}
								}
								if (bLine) {
									for (int px = 0; px < grid_width; px++)
										grid[(currentY + py) * grid_width + px] = 0;

									lines.push_back(currentY + py);
								}
							}

						// Score
						score += 15;
						if (!lines.empty()) score += (1 << lines.size()) * 100;
						DisplayScore(score);


						// Choose next piece
						currentX = grid_width / 2;
						currentY = 0;
						currentRotation = rand() % 4;
						

						

						// If piece doesn't fit - game over
						is_game_over = !DoesPieceFit(currentPiece, currentRotation, currentX, currentY, grid);
						if (is_game_over)
						{
							GameOver(score);
						}

						
					}
				}

				// DRAW FRAME ==========================================================================================================

				std::vector<int> final_array;
				for (int i = 0; i < grid_height * grid_width; i++)
				{
					final_array.push_back(0);
				}

				// Add current piece to final array
				for (int px = 0; px < 4; px++) {
					for (int py = 0; py < 4; py++) {
						if (shape[currentPiece][Rotate(px, py, currentRotation)] != 0) {
							final_array[(px + currentX) + (py + currentY)*grid_width] = shape[currentPiece][Rotate(px, py, currentRotation)];
						}
					}
				}

				// Add other pieces to final array
				for (int x = 0; x < grid_width; x++)
					for (int y = 0; y < grid_height; y++) {
						if (grid[x + y * grid_width] != 0) {
							final_array[x + y * grid_width] = grid[x + y * grid_width];
						}
					}

				//Draw Final Array to the screen
				for (int x = 0; x < grid_width; x++)
					for (int y = 0; y < grid_height; y++) {
						if (final_array[x + y * grid_width] != 0 && square_indexes[x + y * grid_width] == 0) {
							float vertecies[] = {
								-1.0 + x * cell_size + margin_horizontal,
								1.0 - y * cell_size - margin_vertical,

								-1.0 + cell_size + x * cell_size + margin_horizontal,
								1.0 - y * cell_size - margin_vertical,

								-1.0 + cell_size + x * cell_size + margin_horizontal,
								1.0 - cell_size - y * cell_size - margin_vertical,

								-1.0 + x * cell_size + margin_horizontal,
								1.0 - cell_size - y * cell_size - margin_vertical
							};

							float xcord = (vertecies[0] + vertecies[2] + vertecies[4] + vertecies[6]) / 4;
							float ycord = (vertecies[1] + vertecies[3] + vertecies[5] + vertecies[7]) / 4;


							int a = Square(xcord, ycord, cell_size / 2, cell_size / 2, GetBlockTexture(final_array[x + y * grid_width]));
							square_indexes[x + y * grid_width] = a;
						}
						else if (final_array[x + y * grid_width] == 0 && square_indexes[x + y * grid_width] != 0) {
							SquareRemove(square_indexes[x + y * grid_width]);
							square_indexes[x + y * grid_width] = 0;
						}
					}

				if (!lines.empty()) {
					// Draw Line with boom texture

					for (auto &py : lines)
						for (int px = 0; px < grid_width; px++) {

							pause_a_bit = true;
							float vertecies[] = {
								-1.0 + (px)* cell_size + margin_horizontal,
								1.0 - (py)* cell_size - margin_vertical,

								-1.0 + cell_size + (px)* cell_size + margin_horizontal,
								1.0 - (py)* cell_size - margin_vertical,

								-1.0 + cell_size + (px)* cell_size + margin_horizontal,
								1.0 - cell_size - (py)* cell_size - margin_vertical,

								-1.0 + (px)* cell_size + margin_horizontal,
								1.0 - cell_size - (py)* cell_size - margin_vertical
							};
							float xcord = (vertecies[0] + vertecies[2] + vertecies[4] + vertecies[6]) / 4;
							float ycord = (vertecies[1] + vertecies[3] + vertecies[5] + vertecies[7]) / 4;


							int a = Square(xcord, ycord, cell_size / 2, cell_size / 2, boom_texture);
							linesIndexes.push_back(a);




						}

					for (auto &v : lines)
						for (int px = 0; px < grid_width; px++)
						{
							for (int py = v; py > 0; py--)
								grid[py * grid_width + px] = grid[(py - 1) * grid_width + px];
							grid[px] = 0;
						}

					lines.clear();

				}

				// END DRAW FRAME =====================================================================================================
			}


			//Checks if enter is pressed to restart the game
			if (Key_Enter == GLFW_PRESS && is_game_over)
			{
				currentPiece = rand() % 7;
				currentRotation = 3;
				currentX = grid_width / 2;
				currentY = 0;

				ticksToForceDown = startingticksToForceDown;

				forceDown = false;
				pieceCount = 0;
				score = 0;

				pause_a_bit = false;
				is_game_over = false;

				for (int i = 0; i < grid_width * grid_height; i++)
					grid[i] = 0;
				
				if (modas != 1)
				{
					bestPlan.score = -10000;
					// CALCULATE BEST MOVE
					for (int r = 0; r < 4; r++) {
						for (int x = -3; x < grid_width + 3; x++) {
							Plan plan = Plan(x, r);
							CalculatePlanScore(plan, grid);
							if (modas == 2)
							{
								if (bestPlan.score < plan.score) bestPlan = plan;
							}
							else if (modas == 3)
							{
								if (bestPlan.score > plan.score && plan.score > -100000) bestPlan = plan;
							}
						}
					}
				}

				SquareRemove(GameOverLenta);
				DisplayScore(0);
			}
		}
	}
	if (modas == 2) tick = 10;
	else tick = 50;
	Draw(); //Laikyk ðità funkcijà apaèioje
}

int TetrisGame::GetBlockTexture(int n) {
	switch (n) {
		case 1: return tetris_block_texture_1;
		case 2: return tetris_block_texture_2;
		case 3: return tetris_block_texture_3;
		case 4: return tetris_block_texture_4;
		case 5: return tetris_block_texture_5;
		case 6: return tetris_block_texture_6;
		default: return tetris_block_texture_1;
	}
}

int TetrisGame::Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees			
		pi = py * 4 + px;
		break;


	case 1: // 90 degrees			
		pi = 12 + py - (px * 4);
		break;


	case 2: // 180 degrees			
		pi = 15 - (py * 4) - px;
		break;


	case 3: // 270 degrees			
		pi = 3 - py + (px * 4);
		break;
	}

	return pi;
}

bool TetrisGame::DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY, std::vector<int> &mygrid)
{
	int rotated_shape[16];
	// All Field cells >0 are occupied
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * grid_width + (nPosX + px);

			rotated_shape[px + py * 4] = shape[nTetromino][pi];
			if (nPosX + px >= 0 && nPosX + px < grid_width)
			{
				if (nPosY + py >= 0 && nPosY + py < grid_height)
				{
					// In Bounds so do collision check
					if (shape[nTetromino][pi] != 0 && mygrid[fi] != 0) {
						return false; // fail on first hit
					}

				}
			}
		}

	for (int px = 0; px < 4; px++) {
		for (int py = 0; py < 4; py++)
		{

			if (rotated_shape[px + 4 * py] != 0 && px + nPosX > grid_width - 1) return false;
			if (rotated_shape[px + 4 * py] != 0 && px + nPosX < 0) return false;
			if (rotated_shape[px + 4 * py] != 0 && py + nPosY > grid_height - 1) return false;

		}

	}

	return true;
}

void TetrisGame::DisplayScore(int score)
{
	int a = score;
	float ilgis = 0.05f;
	float plotis = 0.04f;
	float xPos = 0.95f;
	float yPos = 0.8f;
	for (int i = 0; i < skaiciai.size(); i++)
	{
		SquareRemove(skaiciai[i]);
	}
	skaiciai.clear();
	if(score == 0)
		skaiciai.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[0]));
	else
	while (a > 0)
	{
		int temp = a % 10;
		a /= 10;
		skaiciai.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[temp]));
		xPos -= 0.04f;
	}
}

void TetrisGame::GameOver(int score)
{
	GameOverLenta = Square(0, 0, 0.4f, 0.65f, tekstura4);
	int n = 0;
	int a = score;
	highscore = max(highscore, score);
	float ilgis = 0.05f;
	float plotis = 0.04f;
	float xPos = 0;
	float yPos = 0.05f;
	while (a > 0)
	{
		a /= 10;
		n++;
	}
	a = score;
	xPos = (double)(n * ilgis + (n - 1) * 0.04f) / 6;
	if (score == 0)
		skaiciai.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[0]));
	else
		while (a > 0)
		{
			int temp = a % 10;
			a /= 10;
			skaiciai.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[temp]));
			xPos -= 0.04f;
		}
	//==================================================================================
	n = 0;
	a = highscore;
	yPos = -0.13f;
	while (a > 0)
	{
		a /= 10;
		n++;
	}
	a = highscore;
	xPos = (double)(n * ilgis + (n - 1) * 0.04f) / 6;
	while (a > 0)
	{
		int temp = a % 10;
		a /= 10;
		skaiciai.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[temp]));
		xPos -= 0.04f;
	}
}

void TetrisGame::UnloadScene()
{
	Objektai.clear();
	for (int i = 0; i < TexSeklys.size(); i++)
	{
		TexSeklys[i] = 0;
	}
}

void TetrisGame::DisplayNumber(float x, float y, float font, int number, std::vector<int> &skaiciumasyvas)
{
	int a = number;
	float ilgis = (double)(font * 5) / 100.0;
	float plotis = (double)(font * 4) / 100.0;
	float xPos = x;
	float yPos = y;
	for (int i = 0; i < skaiciumasyvas.size(); i++)
	{
		SquareRemove(skaiciumasyvas[i]);
	}
	skaiciumasyvas.clear();
	if (number == 0)
		skaiciumasyvas.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[0]));
	else
		while (a > 0)
		{
			int temp = a % 10;
			a /= 10;
			skaiciumasyvas.push_back(Square(xPos, yPos, plotis, ilgis, SkaiciuTeksturos[temp]));
			xPos -= (double)(font * 4) / 100.0;
		}
}

void TetrisGame::UndisplayNumber(std::vector<int>& skaiciumasyvas)
{
	for (int i = 0; i < skaiciumasyvas.size(); i++)
	{
		SquareRemove(skaiciumasyvas[i]);
	}
	skaiciumasyvas.clear();
}

bool TetrisGame::DeltaTime(int goal)
{
	int timeDif = clock() - oldTime;
	if (timeDif >= goal)
	{
		oldTime = clock();
		return true;
	}
	return false;
}

//Þemiau neik. Jei reikia funkcijø, daryk virð
	void TetrisGame::Draw()
	{
		int k = 1;
		teksturos[0].Bind();
		for (int i = 0; i < Objektai.size(); i++)
		{
			if (i == TexSeklys[k - 1])
			{
				while (k < TexSeklys.size() - 1 && TexSeklys[k - 1] == TexSeklys[k])
					k++;
				teksturos[k].Bind();
				k++;
			}
			Objektai[i]._Draw(shaderis, rendereris);
		}
	}

	int TetrisGame::Square(float x, float y, float width, float length, int Tekstura)
	{
		_Square temp(x, y, width, length, visoSquares + 1);
		Objektai.insert(Objektai.begin() + TexSeklys[Tekstura], temp);
		for (int i = Tekstura; i < TexSeklys.size(); i++)
		{
			TexSeklys[i]++;
		}
		visoSquares++;
		return visoSquares;
	}

	void TetrisGame::SquareRemove(int square)
	{
		int i = 0;
		for (i = 0; i < Objektai.size(); i++)
		{
			if (Objektai[i].nr == square)
				break;
		}
		Objektai.erase(Objektai.begin() + i);
		if (i < TexSeklys[0])
		{
			for (int k = 0; k < TexSeklys.size(); k++)
			{
				TexSeklys[k]--;
			}
		}
		else
			for (int y = 1; y < TexSeklys.size(); y++)
			{
				if (i < TexSeklys[y] && i >= TexSeklys[y - 1])
				{
					for (int k = y; k < TexSeklys.size(); k++)
					{
						TexSeklys[k]--;
					}
					break;
				}
			}
		square = NULL;
	}

	void TetrisGame::Move(int square, float x, float y)
	{
		int i;
		for (i = 0; i < Objektai.size(); i++)
		{
			if (Objektai[i].nr == square)
				break;
		}
		Objektai[i].Move(x, y);
	}

	void TetrisGame::MoveA(int square, float x, float y)
	{
		int i;
		for (i = 0; i < Objektai.size(); i++)
		{
			if (Objektai[i].nr == square)
				break;
		}
		Objektai[i].MoveA(x, y);
	}

	int TetrisGame::AddTexture(std::string path)
	{
		Texture temp(path);
		if (TexSeklys.size() == 0)
			TexSeklys.push_back(0);
		else
			TexSeklys.push_back(TexSeklys[TexSeklys.size() - 1]);
		teksturos.push_back(temp);
		return teksturos.size() - 1;
	}

	void TetrisGame::TextureRemove(int &texture) //Ðitos funkcijos esminë problema yra ta, kad paðalinus 1 teksturà, visø kitø tekstûrø numeriai tampa klaidingais
	{
		teksturos.erase(teksturos.begin() + texture);
		TexSeklys.erase(TexSeklys.begin() + texture);
		texture = NULL;
	}

	TetrisGame::TetrisGame(Shader & shader, Renderer & renderer)
		: shaderis(shader), rendereris(renderer)
	{
	}
