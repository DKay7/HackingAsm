#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sys/stat.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
bool WAS_PATCHED = false;
bool PATCHING_IN_PROGRESS = false;

void start_patch (const char* filename);
size_t count_file_size (FILE *file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (void)
{   
    sf::RenderWindow window(sf::VideoMode(600, 200), "Keygen Vx7800Ti");
	window.setFramerateLimit(60);

	sf::Font font;
    sf::Vector2u TextureSize;  //Added to store picaFramesTexture size.
    sf::Vector2u WindowSize;   //Added to store window size.
	sf::Text titleText("Patcher for Sasha's shit", font, 22);
	sf::Text infoText("F2 to patch / ESC to quit", font, 14);
	sf::Text resultText("Patching complete!", font, 20);
	sf::Text waitText("Patching in progress...", font, 20);
    sf::Texture BackgroundTexture;
    sf::Sprite background;
    sf::SoundBuffer music_buf;
    sf::Sound sound;

    music_buf.loadFromFile("data/cring_mus.wav");
    sound.setBuffer(music_buf);
    sound.setLoop(true);
    sound.play();
    
    font.loadFromFile("data/CringeFont.ttf");
    titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2.0f,
                        textRect.top);
    titleText.setPosition(window.getView().getCenter().x, 5.f);

    infoText.setFillColor(sf::Color::Black);
    textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top);
    infoText.setPosition(window.getView().getCenter().x, 35.f);
    
    resultText.setFillColor(sf::Color::Green);
    textRect = resultText.getLocalBounds();
    resultText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top);
    resultText.setPosition(window.getView().getCenter().x, 75.f);

    waitText.setFillColor(sf::Color::Yellow);
    textRect = waitText.getLocalBounds();
    waitText.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top);
    waitText.setPosition(window.getView().getCenter().x, 75.f);

    BackgroundTexture.loadFromFile("data/background.png");
    TextureSize = BackgroundTexture.getSize();              //Get size of texture.
    WindowSize = window.getSize();                          //Get size of window.
    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.
    background.setTexture(BackgroundTexture);
    background.setScale(ScaleX, ScaleY);                    //Set scale.  

    sf::Texture picaFramesTexture;
    picaFramesTexture.loadFromFile("data/frames.png");

    int pica_rect_width = 300, pica_rect_high = 200;
    sf::IntRect picaRect (900, -50, pica_rect_width, pica_rect_high);
    sf::Sprite picaSprite(picaFramesTexture, picaRect);
    sf::Clock clock;

    sf::Event event;
    while (window.isOpen())
	{   
        if (PATCHING_IN_PROGRESS)
        {
            start_patch("hacking-bin");
        }

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::F2) PATCHING_IN_PROGRESS = true;
			}
		}

        if (clock.getElapsedTime().asSeconds() > 0.25f)
        {
            if (picaRect.left == 3 * pica_rect_width)
                picaRect.left = 0;
            else
                picaRect.left += pica_rect_width;


            picaSprite.setTextureRect(picaRect);
            clock.restart();
        }

		// Выполняем необходимые действия по отрисовке
		window.clear();
        window.draw(background);
        window.draw(titleText);
        window.draw(infoText);
        window.draw(picaSprite);
        if (WAS_PATCHED) window.draw(resultText);
        if (PATCHING_IN_PROGRESS) window.draw(waitText);
		window.display();
	}

    return 0;
}

void start_patch (const char* filename)
{   
    FILE* file = fopen (filename, "r");
    size_t file_size = count_file_size (file);
    char* buffer = (char*) calloc (file_size, sizeof(*buffer));
    fread (buffer, file_size, sizeof(*buffer), file);
    
    long unsigned int* target_pointer = (long unsigned int*) (buffer + 0x18D5); 
    (*target_pointer) = 0xFFFFFB06E8000000;
    // TODO add leave + ret
    fclose(file);

    file = fopen(filename, "w");
    fwrite (buffer, file_size, sizeof(*buffer), file);
    fclose (file);

    PATCHING_IN_PROGRESS = false;
    WAS_PATCHED = true;
    
    free (buffer);
    return;
}

size_t count_file_size (FILE *file)
{   
    struct stat buff;
    fstat (fileno (file), &buff);
    return (size_t) buff.st_size;
}
