#include <iostream>
#include <conio.h>
#include <ctime>

int main()
{
	srand(time(0));
	// init value 
	const int count_figures = 100; 
	bool rungame = true;
	int temp_rungame = 20; 
	int width = 50;
	int height = 20; 
	int ball_x = width / 2; 
	int ball_y = height / 2;
	int center_platform = width / 2;  
	int figures_x[count_figures] = { 0 };
	int figures_y[count_figures] = { 0 }; 

	for (int figure = 0; figure < sizeof(figures_x) / sizeof(figures_x[0]); figure++)
	{
		figures_x[figure] = 1 + rand() % 49;
		figures_y[figure] = 1 + rand() % 5;

	}
	bool find_figure = false;
		// logic value
		// platform
		bool plat_left_flag = false; 
		bool plat_right_flag = true; 
		// ball
		bool right_up_flag = true;
		bool right_down_flag, left_up_flag, left_down_flag;
		right_down_flag = left_down_flag = left_up_flag = false;

		while (rungame)
		{
			//Control (Управление)
			if (_kbhit())
			{
				switch (_getch()) 
				{
				case 75: //Key left Нажатие клавиши влево
					plat_left_flag = true;
					plat_right_flag = false;
					break;
				case 77: //Key right Нажатие клавиши вправо
					plat_left_flag = false;
					plat_right_flag = true;
					break;
				case 27: //Key escape Выход из игрового цикла
					rungame = false;
					break;
				default:
					break;
				}
			}

				//Render (Отрисовка)
				system("cls"); 
				for (int col = 0; col <= height; col++)
				{
					for (int row = 0; row <= width; row++)
					{
						find_figure = false;
						for (int figure = 0; figure < sizeof(figures_x) / sizeof(figures_x[0]); figure++) 
						{
							if (row == figures_x[figure] && col == figures_y[figure])
							{
								std::cout << '&';
								find_figure = true;
								break;
							}
						}
						if (row == 0 || col == 0 || row == width || col == height) 
						{
							std::cout << 'x';
						}
						else if (row == ball_x && col == ball_y) 
						{
							std::cout << 'o';
						}
						else if (col == height - 1 && row == center_platform ||
								 col == height - 1 && row == center_platform - 1 ||
								 col == height - 1 && row == center_platform - 2 ||
								 col == height - 1 && row == center_platform + 1 ||
								 col == height - 1 && row == center_platform + 2)
						{
							std::cout << '_';
						}

						else if (!find_figure)
						{
							std::cout << ' ';
						}
					}
					std::cout << std::endl; 
				}
				// Logic 
				// Platform
		
				if (plat_left_flag) 
				{
					center_platform--;
				}
				else if (plat_right_flag) 
				{
					center_platform++;
				}


					// Ball
			

					if (left_down_flag)
					{
						ball_x--;
						ball_y++;
					}
					else if (left_up_flag)
					{
						ball_x--;
						ball_y--;
					}
					else if (right_down_flag) 
					{
						ball_x++;
						ball_y++;
					}
					else if (right_up_flag)
					{
						ball_x++;
						ball_y--;
					}
						// platform limit - Ограничение платформы краями игрового поля
						if (center_platform >= width - 3) 
						{
							center_platform = width - 3;
						}
						else if (center_platform <= 3)
						{
							center_platform = 3;
						}

							// Rebound
							// platform
					
							if (ball_y == height - 1 && ball_x == center_platform ||
								ball_y == height - 1 && ball_x == center_platform - 1 ||
								ball_y == height - 1 && ball_x == center_platform - 2 ||
								ball_y == height - 1 && ball_x == center_platform + 1 ||
								ball_y == height - 1 && ball_x == center_platform + 2)
							{
								if (right_down_flag)
								{
									right_down_flag = false;
									right_up_flag = true;
								}
								else if (left_down_flag)
								{
									left_down_flag = false;
									left_up_flag = true;
								}

							}
						// figure
				
						for (int figure = 0; figure < sizeof(figures_x) / sizeof(figures_x[0]); figure++)
						{
							if (ball_x == figures_x[figure] && ball_y == figures_y[figure])
							{
								figures_x[figure] = width + 1;
								figures_y[figure] = height + 1;

								if (right_up_flag)
								{
									right_up_flag = false;
									right_down_flag = true;
								}
								else if (left_up_flag)
								{
									left_up_flag = false;
									left_down_flag = true;
								}
								else if (left_down_flag)
								{
									left_down_flag = false;
									left_up_flag = true;
								}
								else if (right_down_flag)
								{
									right_down_flag = false;
									right_up_flag = true;
								}

							}
						}
				// top
		
				if (ball_y == 0)
				{
					if (right_up_flag)
					{
						right_up_flag = false;
						right_down_flag = true;
					}
					else if (left_up_flag)
					{
						left_up_flag = false;
						left_down_flag = true;
					}
				}
		// walls
		// left

		if (ball_x == 0)
		{
			if (left_down_flag)
			{
				left_down_flag = false;
				right_down_flag = true;
			}
			else if (left_up_flag)
			{
				left_up_flag = false;
				right_up_flag = true;
			}
		}

// right

		if (ball_x == width)
		{
			if (right_up_flag)
			{
				right_up_flag = false;
				left_up_flag = true;
			}
			else if (right_down_flag)
			{
				right_down_flag = false;
				left_down_flag = true;
			}
		}
// floor

		if (ball_y == height)
		{
			rungame = false;
		}


	}
	system("pause"); 

}