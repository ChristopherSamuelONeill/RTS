#include <iostream>

#include <fstream>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "Profile.h"
#include "Button.h"
#include "Overlay.h"
#include "TextBox.h"
#include "Game.h"
#include "Sound.h"
#include "TextureObject.h"

using namespace std;
using namespace sf;

void mainMenu(bool tutorial);
void profileMenu(bool tutorial);
void settingsMenu(bool tutorial);
void playMenu();
void play(string path);
void LoadLevel();
void editor();

void resetSelectors();

bool DEBUGMODE = true;
Profile *player;
SoundObject *sound;
TextureObject *m_Gametextures;// \brief handle to all game textures


//selections bools
//_----------------------------------------OLD CODE-------------------------------------
bool RoadSelectorBool = false; // true while choosing road
bool LightSelectorBool = false; // true while choosing roads
bool unitsSelectorBool = false; // true while altering units
bool PedSelectorBool = false; // true while altering pedestrians
bool StartEndPointsBool = false; // true while altering start and end points

bool placingBool = false; // true while placing roads

int tutorialState = 0;

int main()
{
	player = Profile::getInstance();
	sound = SoundObject::getInstance();
	m_Gametextures = TextureObject::getInstance();
	player->loadProfile("default");
	sound->loadSounds();
	m_Gametextures->loadTextures();

	
	//luanch game
	if (DEBUGMODE) cout << "Launching Game" << endl;

	//open profile list
	fstream file;
	string lineData;
	string tempProfile;
	vector<string> profileNames;

	file.open("Assets/profiles/profileList.txt");

	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream iss(lineData);
			iss.str(lineData);
			iss >> tempProfile;
			profileNames.push_back(tempProfile);
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/profileList.txt" << endl;
	}

	file.close();
	if (DEBUGMODE) cout << "Profiles present : " << profileNames.size() << endl;
	//check to see if any profiles were present
	if (profileNames.size() > 0)
	{
		// luanch profileMenu in normal mode
		player->loadProfile("default");
		tutorialState = 11;
		//profileMenu(false);

		string mode;
		cout << endl << endl << "=================================================================" << endl << "Test mode : (ben type Arena) : ";
		cin >> mode;

		play(mode);
	}
	else
	{
		if (DEBUGMODE) cout << "Tutorial mode" << endl;
		if (DEBUGMODE) cout << "Loading Default profile" << endl;
		player->loadProfile("default");
		if (DEBUGMODE) cout << "Default profile loaded" << endl;
		// luanch menu in tutorial mode

		mainMenu(true);
		
	}

	

	
	return 0;
}

void mainMenu(bool tutorial)
{
	Texture mainMenuBackgroundTex;
	if (!mainMenuBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};

	if (tutorial)
	{
		//default.txt is now the profile
		//create main menu assets ......................
	

		//main menu background-------------------------
		RectangleShape mainMenuBackgroundRect;
		Sprite mainMenuBackgroundSprite;
		
		mainMenuBackgroundRect.setPosition(0, 0);
		mainMenuBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		mainMenuBackgroundRect.setFillColor(Color::Blue);

		mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTex);
		mainMenuBackgroundSprite.setScale(Vector2f(1, 1));
		mainMenuBackgroundSprite.setPosition(mainMenuBackgroundRect.getPosition());


		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Main Menu");
		title.setCharacterSize(50*resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Button play("Play", Vector2f(middleOfScreen.x, 100 * resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");
		Button profile("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button settings("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");
		Button quit("Quit", Vector2f(middleOfScreen.x, 550 * resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");
	
		
		Button profileGrey("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");
		Button settingsGreen ("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		
		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 -  (250 * resolutionScale.x), player->m_sfResolution.y / 2 - (250 * resolutionScale.y));

		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to Traffic Management !\n\t Please click on Profiles\n\n\n(Click on messages like this to close them)");
		Overlay secondOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tYou have now created your profile!\n\t Please click on settings\n\n\n");
		if (tutorialState >= 6) firstOverlayMessage.m_bDraw = false;
		secondOverlayMessage.m_bDraw = false;
		if (tutorialState == 6)secondOverlayMessage.m_bDraw = true;

		RenderWindow window(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);


		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{
				
				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				
				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (settingsGreen.m_bClicked(sfMousePos) && tutorialState == 7)
						{
							//close and open profile menu
							tutorialState = 8;  
							window.close();
							settingsMenu(true);

						}
						if (secondOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 6)
						{
							
							tutorialState = 7;
							secondOverlayMessage.m_bDraw = false;

						}
						if (profile.m_bClicked(sfMousePos) && tutorialState == 1)
						{
							//close and open profile menu
							tutorialState = 2;
							window.close();
							profileMenu(true);

						}
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 0)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 1;
							
						}

						
					}
				}
			}


			window.clear(Color::Green);

			window.draw(mainMenuBackgroundSprite);
			window.draw(title);
			
			// buttons
			window.draw(play);
			window.draw(profile);
			if (tutorialState == 7)
			{
				window.draw(profileGrey);
			}
			else
			{
				window.draw(profile);
			}
			if (tutorialState == 7)
			{
				window.draw(settingsGreen);
		
			}
			else
			{
				window.draw(settings);
			}
			window.draw(quit);

			// first overlay
			window.draw(firstOverlayMessage);
			window.draw(secondOverlayMessage);
			window.display();
		}

	}
	else if (!tutorial)
	{
		//we now have a profile
		//create main menu assets ......................
		
		player->m_sProfileName;

		//main menu background-------------------------
		RectangleShape mainMenuBackgroundRect;
		Sprite mainMenuBackgroundSprite;
	
		mainMenuBackgroundRect.setPosition(0, 0);
		mainMenuBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		mainMenuBackgroundRect.setFillColor(Color::Blue);

		mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTex);
		mainMenuBackgroundSprite.setScale(Vector2f(1, 1));
		mainMenuBackgroundSprite.setPosition(mainMenuBackgroundRect.getPosition());


		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Main Menu");
		title.setCharacterSize(50 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Button play("Play", Vector2f(middleOfScreen.x, 100 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button profile("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button settings("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button quit("Quit", Vector2f(middleOfScreen.x, 550 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");

		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 - (250 * resolutionScale.x), player->m_sfResolution.y / 2 - (250 * resolutionScale.y));
		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tYou have now finished the tutorial! \n\nClick play to start playing");
		if (tutorialState == 11)firstOverlayMessage.m_bDraw = false;

		RenderWindow window;
		if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu", Style::Fullscreen);
		else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu");

		


		window.setFramerateLimit(60);
		

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
					
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 10)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 11; // finished

						}
						if (play.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							playMenu();

						}
						if (settings.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							settingsMenu(false);

						}
						if (profile.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							profileMenu(false);

						}
						if (quit.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close(); // Allows window to close when 'X' is pressed
							player->saveProfile();
							return;

						}
					}
				}
			}


			window.clear(Color::Green);

			window.draw(mainMenuBackgroundSprite);
			window.draw(title);

			// buttons
			window.draw(play);
			window.draw(profile);
			window.draw(settings);
			window.draw(quit);

			// first overlay
			window.draw(firstOverlayMessage);
			window.display();
		}

	}

}

void profileMenu(bool tutorial)
{
	Texture profileBackgroundTex;
	if (!profileBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};

	if (tutorial)
	{
		//for profile screen
		// enter at tutorial state 2
		// after close message tutorial state 3
		// after click new tutorial sate 4
		

		//create profile assets ......................

		//profile background-------------------------
		RectangleShape profileBackgroundRect;
		Sprite profileBackgroundSprite;


		profileBackgroundRect.setPosition(0, 0);
		profileBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		profileBackgroundRect.setFillColor(Color::Blue);

		profileBackgroundSprite.setTexture(profileBackgroundTex);
		profileBackgroundSprite.setScale(Vector2f(1, 1));
		profileBackgroundSprite.setPosition(profileBackgroundRect.getPosition());



		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Button New("New", Vector2f(middleOfScreen.x - buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button Select("Select", Vector2f(middleOfScreen.x , 100 + middleOfScreen.y *resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");
		Button Delete("Delete", Vector2f(middleOfScreen.x + buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, resolutionScale, "Button_Grey");


		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Profiles");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));
	
		//Enter you name Sprite
		RectangleShape listOfProfilesRect;
		Sprite listOfProfilesSprite;
		Texture listOfProfilesTex;
		if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenuEmpty.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x , -120 + middleOfScreen.y * resolutionScale.y));
		listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
		listOfProfilesRect.setFillColor(Color::Blue);

		listOfProfilesSprite.setTexture(listOfProfilesTex);
		listOfProfilesSprite.setScale(Vector2f( 1 * resolutionScale.x , 1 * resolutionScale.y ));
		listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());

		//Enter you name Sprite
		RectangleShape nameEntryRect;
		Sprite nameEntrySprite;
		Texture nameEntryTex;
		if (!nameEntryTex.loadFromFile("Assets/textures/ProfileEnterBackground.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		nameEntryRect.setPosition((player->m_sfResolution.x /2) - (579 /2 * resolutionScale.x), (player->m_sfResolution.y / 2) - (144 / 2 * resolutionScale.y));
		nameEntryRect.setSize(Vector2f(579 * resolutionScale.x, 144*resolutionScale.y));
		nameEntryRect.setFillColor(Color::Blue);

		nameEntrySprite.setTexture(nameEntryTex);
		nameEntrySprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
		nameEntrySprite.setPosition(nameEntryRect.getPosition());

		//create text box 
		Vector2f edgeOfTextBox(nameEntryRect.getPosition().x + (579 * resolutionScale.x) / 8, nameEntryRect.getPosition().y + (144 * resolutionScale.y) / 2);
		TextBox playerEnterNameBox("", edgeOfTextBox , Vector2f(343*resolutionScale.x, 37*resolutionScale.y), "Textbox");
		Button Submit("Submit", Vector2f(edgeOfTextBox.x + 343 * resolutionScale.x, edgeOfTextBox.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale,  "Button_Green");

		//create overlays
		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 - (300 * resolutionScale.x), player->m_sfResolution.y / 2 - (300 * resolutionScale.y));
		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to the Profile Menu !\n\t There are currently no profiles available.\n\n\n Please click New to create a profile.");
		Overlay secondOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tPlease enter your name into the box !\n\t And click submit when your finished.");
		

		firstOverlayMessage.m_bDraw = true;
		secondOverlayMessage.m_bDraw = false;
		
		RenderWindow window(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
			
				if (event.type == sf::Event::KeyPressed && playerEnterNameBox.m_bIsEntering == true)
				{
					playerEnterNameBox.takeInput(event.key.code);
				}


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (tutorialState == 5 && Submit.m_bClicked(sfMousePos))
						{
							tutorialState = 6;
							//create a new profile with there name

							player->newProfile(playerEnterNameBox.m_sText);
							window.close();
							mainMenu(true);
						}

						if (playerEnterNameBox.m_bClicked(sfMousePos) && tutorialState == 5)
						{
							playerEnterNameBox.m_bIsEntering = true;
						}

						if (secondOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 4)
						{
							tutorialState = 5;
						}
						if (New.m_bClicked(sfMousePos) && tutorialState == 3)
						{
							//change profile menu state
							tutorialState = 4;
						}
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 2)
						{
							tutorialState = 3;
						}


					}
				}
			}


			window.clear(Color::Green);
			window.draw(profileBackgroundSprite);
		
			window.draw(title);

			// buttons
			if (tutorialState != 4 && tutorialState != 5)
			{
				window.draw(listOfProfilesSprite);
				window.draw(New);
				window.draw(Select);
				window.draw(Delete);
			}
			else // enter player name
			{
				
				window.draw(nameEntrySprite);
				window.draw(playerEnterNameBox);
				window.draw(Submit);
			}

			if(tutorialState == 3)firstOverlayMessage.m_bDraw = false;
			if (tutorialState == 4)secondOverlayMessage.m_bDraw = true;
			if (tutorialState == 5)secondOverlayMessage.m_bDraw = false;

			// overlays		
			window.draw(firstOverlayMessage);
			window.draw(secondOverlayMessage);


			window.display();
		}

	}
	else if (!tutorial)
	{
		
		//create profile assets ......................

		//profile background-------------------------
		RectangleShape profileBackgroundRect;
		Sprite profileBackgroundSprite;
		
		profileBackgroundRect.setPosition(0, 0);
		profileBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		profileBackgroundRect.setFillColor(Color::Blue);

		profileBackgroundSprite.setTexture(profileBackgroundTex);
		profileBackgroundSprite.setScale(Vector2f(1, 1));
		profileBackgroundSprite.setPosition(profileBackgroundRect.getPosition());



		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Button New("New", Vector2f(middleOfScreen.x - buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button Select("Select", Vector2f(middleOfScreen.x, 100 + middleOfScreen.y *resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
		Button Delete("Delete", Vector2f(middleOfScreen.x + buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");


		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Profiles");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		//Enter you name Sprite
		RectangleShape listOfProfilesRect;
		Sprite listOfProfilesSprite;
		Texture listOfProfilesTex;
		if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenu.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x, -120 + middleOfScreen.y * resolutionScale.y));
		listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
		listOfProfilesRect.setFillColor(Color::Blue);

		listOfProfilesSprite.setTexture(listOfProfilesTex);
		listOfProfilesSprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
		listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());

		
		//create text box 
		Vector2f edgeOfTextBox(listOfProfilesRect.getPosition().x , listOfProfilesRect.getPosition().y + (144 * resolutionScale.y) / 2);
		TextBox playerEnterNameBox("Enter profile name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
	

		RenderWindow window(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Profiles Menu");
		window.setFramerateLimit(60);

		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 - (250 * resolutionScale.x), player->m_sfResolution.y / 2 - (250 * resolutionScale.y));
		Overlay failedOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tThe Profile you entered does not exist \n\nPlease try again");
		failedOverlayMessage.m_bDraw = false;

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}

				if (event.type == sf::Event::KeyPressed && playerEnterNameBox.m_bIsEntering == true)
				{
					playerEnterNameBox.takeInput(event.key.code);
				}


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{

						if (failedOverlayMessage.m_bClicked(sfMousePos) && failedOverlayMessage.m_bDraw == true)
						{
							failedOverlayMessage.m_bDraw = false;
						}

						if (Select.m_bClicked(sfMousePos))
						{
							if (player->loadProfile(playerEnterNameBox.m_sText))
							{
								window.close();
								mainMenu(false);
							}
							else
							{
								playerEnterNameBox.m_sText.clear();
								failedOverlayMessage.m_bDraw = true;
							
							}
							
							
						}
						

						if (Delete.m_bClicked(sfMousePos))
						{
							// open profile list
							fstream file;
							string lineData;
							string tempProfile;
							vector<string> profileNames;

							file.open("Assets/profiles/profileList.txt");
							if (DEBUGMODE) cout << "opening Profile list" << endl;
							if (file.is_open())
							{
								while (getline(file, lineData))
								{
									istringstream iss(lineData);
									iss.str(lineData);
									iss >> tempProfile;
									profileNames.push_back(tempProfile);
								}
							}
							else
							{
								cout << "Couldnt Open file ... Assets/profiles/profileList.txt" << endl;
							}

							file.close();

							//search vector of names for what was entered
							for (int i = 0; i < profileNames.size(); i++)
							{
								if (profileNames[i] == playerEnterNameBox.m_sText+".txt")
								{
									//remove the name
									profileNames.erase(profileNames.begin() + i);
								}
							}



							//ammend profile list
							ofstream ofile;
							ofile.open("Assets/profiles/profileList.txt");

							for (int i = 0; i < profileNames.size(); i++)
							{
								ofile << profileNames[i] << endl;
							}

							window.close();
							profileMenu(false);
						}

						if (playerEnterNameBox.m_bClicked(sfMousePos) )
						{
							playerEnterNameBox.m_bIsEntering = true;
						}

						
						if (New.m_bClicked(sfMousePos))
						{
							//create a new profile with there name

							player->newProfile(playerEnterNameBox.m_sText);
							window.close();
							mainMenu(false);
						
						}
						


					}
				}
			}


			window.clear(Color::Green);
			window.draw(profileBackgroundSprite);
			
			window.draw(title);
			window.draw(listOfProfilesSprite);
			window.draw(playerEnterNameBox);
			window.draw(New);
			window.draw(Select);
			window.draw(Delete);
			window.draw(failedOverlayMessage);

			window.display();
		}

	}

}

void settingsMenu(bool tutorial)
{
	if (tutorial)
	{
		//main menu background-------------------------
		RectangleShape settingsBackgroundRect;
		Sprite settingsBackgroundSprite;
		Texture settingsBackgroundTex;
		if (!settingsBackgroundTex.loadFromFile("Assets/textures/settingsWindow.png"))
		{
			cout << "Error: settingsWindow.png was unable to load.";
		};
		settingsBackgroundRect.setPosition(0, 0);
		settingsBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		settingsBackgroundRect.setFillColor(Color::Blue);

		//settingsBackgroundSprite.setTextureRect({ 0,0,(int)player->m_sfResolution.x,(int)player->m_sfResolution.y });
		settingsBackgroundSprite.setScale(Vector2f(player->m_sfResolution.x / 3840, player->m_sfResolution.y / 2160));
		settingsBackgroundSprite.setTexture(settingsBackgroundTex);
		settingsBackgroundSprite.setPosition(settingsBackgroundRect.getPosition());

		RectangleShape settingsRect;
		settingsRect.setPosition(player->m_sfResolution.x / 8, player->m_sfResolution.y / 8);


		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Settings");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 - (250 * resolutionScale.x), player->m_sfResolution.y / 2 - (250 * resolutionScale.y));

		//create text box 
		Vector2f TextBoxStart(180 * resolutionScale.x, 300 * resolutionScale.y);
		string s;
		s = to_string(player->m_iGameAudioVolume);

		TextBox gameVolume("Game Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button gameVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;
		s = to_string(player->m_iMusicAudioVolume);

		TextBox musicVolume("Music Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button musicVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;
		s = to_string(player->m_iInterfaceAudioVolume);


		TextBox interfaceVolume("Interface Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button interfaceVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");


		s = to_string(player->m_sfResolution.x);

		TextBoxStart = Vector2f(700 * resolutionScale.x, 300 * resolutionScale.y);

		TextBox resolutionX("Resolution : x " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionXSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;;

		s = to_string(player->m_sfResolution.y);
		TextBox resolutionY("Resolution : y " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionYSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;


		if (player->m_bFullscreen == true) s = "Yes";
		if (player->m_bFullscreen == false) s = "No";

		TextBox fullScreen("Fullscreen Mode " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button fullScreenSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");


		Button Save("Save", Vector2f(settingsRect.getPosition().x, player->m_sfResolution.y - buttonSize.y), buttonSize, resolutionScale, "Button_Green");
		Button Cancel("Cancel", Vector2f(settingsRect.getPosition().x + 3 * buttonSize.x, player->m_sfResolution.y - buttonSize.y), buttonSize, resolutionScale, "Button_Grey");

		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to the settings screen !\n\t Here you can alter any settings you wish\n\n\n Click save when your done.");

		RenderWindow window(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);


		while (window.isOpen())
		{
			 
			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}

				if (event.type == sf::Event::KeyPressed && tutorialState == 9)
				{
					gameVolume.takeInput(event.key.code);
					musicVolume.takeInput(event.key.code);
					interfaceVolume.takeInput(event.key.code);
					resolutionX.takeInput(event.key.code);
					resolutionY.takeInput(event.key.code);
					fullScreen.takeInput(event.key.code);


				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (tutorialState == 9 && Save.m_bClicked(sfMousePos))
						{
							player->saveProfile();
							window.close();
							tutorialState = 10;
							mainMenu(false);

						}

					
						if (tutorialState == 9  )
						{
							if (gameVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = true;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (musicVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = true;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (interfaceVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = true;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (resolutionX.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = true;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (resolutionY.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = true;
								fullScreen.m_bIsEntering = false;
							}
							if (fullScreen.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = true;
							}
						
						}

						if (tutorialState == 9 && fullScreenSubmit.m_bClicked(sfMousePos))
						{
							if (fullScreen.m_sText == "yes")	player->m_bFullscreen = true;
							else if (fullScreen.m_sText == "no")	player->m_bFullscreen = false;
							else player->m_bFullscreen = false;
							
							
						}
						if (tutorialState == 9 && gameVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = gameVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iGameAudioVolume = value;
							}
						}
						
						if (tutorialState == 9 && musicVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = musicVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iMusicAudioVolume = value;
							}

						}

						if (tutorialState == 9 && interfaceVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = interfaceVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iInterfaceAudioVolume = value;
							}

						}
						if (tutorialState == 9 && resolutionXSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionX.m_sText;
							int value = atoi(input.c_str()); 
							if (value >= 800 && value <= 3840)
							{
								player->m_sfResolution.x = value;
							}
						}
						if (tutorialState == 9 && resolutionYSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionY.m_sText;
							int value = atoi(input.c_str());
							if (value >= 600 && value <= 2160)
							{
								player->m_sfResolution.y = value;
							}
						}

						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 8)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 9;

						}

					}
				}
			}


			


			window.clear(Color::Green);

			window.draw(settingsBackgroundSprite);
			window.draw(title);

			// buttons
			window.draw(gameVolume);
			window.draw(gameVolumeSubmit);
			window.draw(interfaceVolume);
			window.draw(interfaceVolumeSubmit);
			window.draw(musicVolume);
			window.draw(musicVolumeSubmit);

			window.draw(resolutionX);
			window.draw(resolutionXSubmit);
			window.draw(resolutionY);
			window.draw(resolutionYSubmit);
			window.draw(fullScreen);
			window.draw(fullScreenSubmit);

			window.draw(Save);
			window.draw(Cancel);

			// first overlay
			window.draw(firstOverlayMessage);
		
			window.display();
		}

	}
	else
	{
		player = Profile::getInstance();

		//main menu background-------------------------
		RectangleShape settingsBackgroundRect;
		Sprite settingsBackgroundSprite;
		Texture settingsBackgroundTex;
		if (!settingsBackgroundTex.loadFromFile("Assets/textures/settingsWindow.png"))
		{
			cout << "Error: settingsWindow.png was unable to load.";
		};
		settingsBackgroundRect.setPosition(0, 0);
		settingsBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
		settingsBackgroundRect.setFillColor(Color::Blue);

		//settingsBackgroundSprite.setTextureRect({ 0,0,(int)player->m_sfResolution.x,(int)player->m_sfResolution.y });
		settingsBackgroundSprite.setScale(Vector2f(player->m_sfResolution.x / 3840, player->m_sfResolution.y / 2160));
		settingsBackgroundSprite.setTexture(settingsBackgroundTex);
		settingsBackgroundSprite.setPosition(settingsBackgroundRect.getPosition());

		RectangleShape settingsRect;
		settingsRect.setPosition(player->m_sfResolution.x / 8, player->m_sfResolution.y / 8);
	

		//Create buttons-------------------------
		Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Settings");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Vector2f middleOfScreenOverlay(player->m_sfResolution.x / 2 - (250 * resolutionScale.x), player->m_sfResolution.y / 2 - (250 * resolutionScale.y));

		//create text box 
		Vector2f TextBoxStart(180 * resolutionScale.x, 300 * resolutionScale.y);
		string s;
		s = to_string(player->m_iGameAudioVolume);

		TextBox gameVolume("Game Volume : " , s , TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button gameVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;
		s = to_string(player->m_iMusicAudioVolume);

		TextBox musicVolume("Music Volume : " , s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button musicVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;
		s = to_string(player->m_iInterfaceAudioVolume);


		TextBox interfaceVolume("Interface Volume : " , s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button interfaceVolumeSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");


		s = to_string(player->m_sfResolution.x);

		TextBoxStart = Vector2f(700 * resolutionScale.x, 300 * resolutionScale.y);

		TextBox resolutionX("Resolution (x) : " , s , TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionXSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;;

		s = to_string(player->m_sfResolution.y);
		TextBox resolutionY("Resolution (y) : " , s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionYSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
		TextBoxStart.y += 100 * resolutionScale.y;


		if (player->m_bFullscreen == true) s = "Yes";
		if (player->m_bFullscreen == false) s = "No";

		TextBox fullScreen("Fullscreen Mode : " , s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button fullScreenSubmit("Submit", Vector2f(TextBoxStart.x + (343 * resolutionScale.x), TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");
	

		Button Save("Save", Vector2f(settingsRect.getPosition().x, player->m_sfResolution.y - buttonSize.y), buttonSize, resolutionScale, "Button_Green");
		Button Cancel("Cancel", Vector2f(settingsRect.getPosition().x + 3 * buttonSize.x, player->m_sfResolution.y - buttonSize.y), buttonSize, resolutionScale, "Button_Green");


		RenderWindow window;
		if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu", Style::Fullscreen);
		else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Settings");

		window.setFramerateLimit(60);

	

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}

				if (event.type == sf::Event::KeyPressed )
				{
					gameVolume.takeInput(event.key.code);
					musicVolume.takeInput(event.key.code);
					interfaceVolume.takeInput(event.key.code);
					resolutionX.takeInput(event.key.code);
					resolutionY.takeInput(event.key.code);
					fullScreen.takeInput(event.key.code);


				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (Save.m_bClicked(sfMousePos))
						{
							player->saveProfile();
							window.close();
							mainMenu(false);

						}

						
						if (Cancel.m_bClicked(sfMousePos))
						{
							window.close();
							mainMenu(false);
						}
						
						if (gameVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = true;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (musicVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = true;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (interfaceVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = true;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (resolutionX.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = true;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (resolutionY.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = true;
							fullScreen.m_bIsEntering = false;
						}
						if (fullScreen.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = true;
						}


						if ( fullScreenSubmit.m_bClicked(sfMousePos))
						{
							if (fullScreen.m_sText == "yes")
							{
								player->m_bFullscreen = true;
								window.close();
								settingsMenu(false);
							}
							else if (fullScreen.m_sText == "no")
							{
								player->m_bFullscreen = false;
								window.close();
								settingsMenu(false);
							}
							else
							{
								player->m_bFullscreen = false;
								fullScreen.m_sText = "No";
							}


						}
						if ( gameVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = gameVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iGameAudioVolume = value;
								window.close();
								settingsMenu(false);
							}
							else
							{
								gameVolume.m_sText = to_string(player->m_iGameAudioVolume);
							}
						}

						if ( musicVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = musicVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iMusicAudioVolume = value;
								window.close();
								settingsMenu(false);
							}
							else
							{
								musicVolume.m_sText = to_string(player->m_iMusicAudioVolume);
							}

						}

						if ( interfaceVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = interfaceVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 100)
							{
								player->m_iInterfaceAudioVolume = value;
								window.close();
								settingsMenu(false);
							}
							else
							{
								interfaceVolume.m_sText = to_string(player->m_iInterfaceAudioVolume);
							}

						}
						if ( resolutionXSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionX.m_sText;
							int value = atoi(input.c_str());
							if (value >= 800 && value <= 3840)
							{
								player->m_sfResolution.x = value;
								window.close();
								settingsMenu(false);
							}
							else
							{
								resolutionX.m_sText = to_string(player->m_sfResolution.x);
							}
						}
						if ( resolutionYSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionY.m_sText;
							int value = atoi(input.c_str());
							if (value >= 600 && value <= 2160)
							{
								player->m_sfResolution.y = value;
								window.close();
								settingsMenu(false);
							}
							else
							{
								resolutionY.m_sText = to_string(player->m_sfResolution.y);
							}
						}

					

					}
				}
			}



			window.clear(Color::Green);

			window.draw(settingsBackgroundSprite);
			window.draw(title);

			// buttons
			window.draw(gameVolume);
			window.draw(gameVolumeSubmit);
			window.draw(interfaceVolume);
			window.draw(interfaceVolumeSubmit);
			window.draw(musicVolume);
			window.draw(musicVolumeSubmit);

			window.draw(resolutionX);
			window.draw(resolutionXSubmit);
			window.draw(resolutionY);
			window.draw(resolutionYSubmit);
			window.draw(fullScreen);
			window.draw(fullScreenSubmit);

			window.draw(Save);
			window.draw(Cancel);

			window.display();
		}
	}

}

void playMenu()
{

	Texture mainMenuBackgroundTex;
	if (!mainMenuBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};

	//we now have a profile
	//create main menu assets ......................
	

	//main menu background-------------------------
	RectangleShape mainMenuBackgroundRect;
	Sprite mainMenuBackgroundSprite;

	mainMenuBackgroundRect.setPosition(0, 0);
	mainMenuBackgroundRect.setSize(Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));
	mainMenuBackgroundRect.setFillColor(Color::Blue);

	mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTex);
	mainMenuBackgroundSprite.setScale(Vector2f(1, 1));
	mainMenuBackgroundSprite.setPosition(mainMenuBackgroundRect.getPosition());


	//Create Positioning variables-------------------------
	Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
	Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
	Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

	Text title;
	Font font;

	if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	title.setFont(font);
	title.setString("Play Menu");
	title.setCharacterSize(50 * resolutionScale.x);
	title.setFillColor(Color(0, 0, 0));
	title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

	Button LevelsButton("Play", Vector2f(50 * resolutionScale.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
	Button LoadButton("Load", Vector2f(350 * resolutionScale.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
	Button EditorButton("Editor",	Vector2f( 650  * resolutionScale.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");
	Button BackButton("Main Menu",	Vector2f( 950 * resolutionScale.x, 400 * resolutionScale.y), buttonSize, resolutionScale, "Button_Green");


	RenderWindow window;
	if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Main Menu", Style::Fullscreen);
	else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Play Menu");
	window.setFramerateLimit(60);


	while (window.isOpen())
	{

		//handle input
		Event event;
		Vector2f sfMousePos;
		while (window.pollEvent(event))
		{

			sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					
					if (EditorButton.m_bClicked(sfMousePos) )
					{
						window.close();
						editor();

					}
					if (LevelsButton.m_bClicked(sfMousePos) )
					{

						window.close();
						string level = "CampaignLevels/level0" +to_string(player->m_uilevel);
						play(level);

					}
					if (LoadButton.m_bClicked(sfMousePos) )
					{
						window.close();
						LoadLevel();

					}
					if (BackButton.m_bClicked(sfMousePos) )
					{
						window.close(); // Allows window to close when 'X' is pressed
						mainMenu(false);

					}
				}
			}
		}


		window.clear(Color::Green);

		window.draw(mainMenuBackgroundSprite);
		window.draw(title);

		// buttons
		window.draw(EditorButton);
		window.draw(LevelsButton);
		window.draw(LoadButton);
		window.draw(BackButton);

		window.display();
	}

}

void play(string path)
{
	Game Level;

	Level = Game(path);


	//Create a window with the specifications of the profile
	RenderWindow window;
	if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), path, Style::Fullscreen);
	else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), path);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//create a view to fill the windowfor game render
	View gameView;
	gameView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	gameView.setCenter(sf::Vector2f(-500, -500));
	gameView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	//create a view to fill the windowfor game render
	View hudView;
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	hudView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
	hudView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	Event event;
	int iMouseWheel;


	//helps scale hud elements
	Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
	Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
	Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));


	Overlay winOverlay(Vector2f(200 * resolutionScale.x, 150 * resolutionScale.y), Vector2f(888 * resolutionScale.x, 500 * resolutionScale.y),
		"Congratulations , you completed the level!\n\n Click anywhere to go back to the menu");
	Overlay loseOverlay(Vector2f(200 * resolutionScale.x, 150 * resolutionScale.y), Vector2f(888 * resolutionScale.x, 500 * resolutionScale.y),
		"Bad Luck , you failed to complete the level\n\n Click anywhere to go back to the menu");

	winOverlay.m_bDraw = false;
	loseOverlay.m_bDraw = false;
	bool bPaused = false;

	gameView.zoom(2.5);

	//input delay
	Clock inputDelay;

	while (window.isOpen())
	{

		Vector2f sfMousePos;

		sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);
		//cout << "mouse :" << sfMousePos.x << " " << sfMousePos << endl;

		//move camera
		float fMoveSpeed = 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			fMoveSpeed *= 3;
		}
		//key presses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			gameView.move(Vector2f(0.0f, -fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			gameView.move(Vector2f(0.0f, fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			gameView.move(Vector2f(-fMoveSpeed, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			gameView.move(Vector2f(fMoveSpeed, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			Level = Game(path);
		}
		

		Time elapsedTime = inputDelay.getElapsedTime();

		if (elapsedTime.asMilliseconds() >= 100.0f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
			{
				if (bPaused == false) bPaused = true;
				else if (bPaused == true) bPaused = false;
				inputDelay.restart();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "CLICKED AT " << sfMousePos.x << " " << sfMousePos.y << endl;
					Level.loopClickables(sfMousePos);
					inputDelay.restart();
				}
			}
			

		}

		
		while (window.pollEvent(event))
		{
			sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);
			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return;
			}

			if (event.type == Event::MouseWheelMoved)
			{
				iMouseWheel = event.mouseWheel.delta;
				if (iMouseWheel > 0)
				{
					//zoom in
					gameView.zoom(0.9);
				}
				if (iMouseWheel < 0)
				{
					//zoom out
					gameView.zoom(1.1);
				}
			}
			
		}
		window.clear(Color::Black);


		//draw the game 
		if (bPaused == false)
		{
			Level.updateScene(0.016f);
		}
		window.setView(gameView);

		

		
		Level.drawScene(window);

		//draw the hud
		window.setView(hudView);

		window.draw(Level.m_sfHudTopBarSprite);


		//show the window
		window.display();
	}

}

void LoadLevel()
{

	//Create a window with the specifications of the profile
	RenderWindow window;
	if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Editor", Style::Fullscreen);
	else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Load Level");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//create a view to fill the windowfor game render
	View gameView;
	gameView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	gameView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
	gameView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	//create a view to fill the windowfor game render
	View hudView;
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	hudView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
	hudView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	Event event;
	int iMouseWheel;


	//helps scale hud elements
	Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
	Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
	Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));


	//Enter your level Sprite
	RectangleShape listOfProfilesRect;
	Sprite listOfProfilesSprite;
	Texture listOfProfilesTex;
	if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenu.png"))
	{
		cout << "Error: ProfileEnterBackground.png was unable to load.";
	};
	listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x, -120 + middleOfScreen.y * resolutionScale.y));
	listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
	listOfProfilesRect.setFillColor(Color::Blue);

	listOfProfilesSprite.setTexture(listOfProfilesTex);
	listOfProfilesSprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
	listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());

	Button QuitButton
	("Exit",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, player->m_sfResolution.y - 90 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);


	//create text box 
	Vector2f edgeOfTextBox(listOfProfilesRect.getPosition().x, listOfProfilesRect.getPosition().y + (144 * resolutionScale.y) / 2);
	TextBox saveLevelEntryName("Enter level name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
	TextBox loadLevelEntryName("Enter level name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");

	Button loadSubmitButton("Submit", Vector2f(edgeOfTextBox.x + 343, edgeOfTextBox.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), resolutionScale, "Button_Green");

	loadLevelEntryName.m_bIsEntering = true;

	while (window.isOpen())
	{

		Vector2f sfMousePos;

		sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);


		//move camera
		float fMoveSpeed = 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			fMoveSpeed *= 3;
		}
		//key presses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			gameView.move(Vector2f(0.0f, -fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			gameView.move(Vector2f(0.0f, fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			gameView.move(Vector2f(-fMoveSpeed, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			gameView.move(Vector2f(fMoveSpeed, 0.0f));
		}
		while (window.pollEvent(event))
		{
			sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);
			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return;
			}

			if (event.type == sf::Event::KeyPressed && loadLevelEntryName.m_bIsEntering == true)
			{
				loadLevelEntryName.takeInput(event.key.code);
			}

			if (event.type == Event::MouseWheelMoved)
			{
				iMouseWheel = event.mouseWheel.delta;
				if (iMouseWheel > 0)
				{
					//zoom in
					gameView.zoom(0.9);
				}
				if (iMouseWheel < 0)
				{
					//zoom out
					gameView.zoom(1.1);
				}
			}
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (loadSubmitButton.m_bClicked(sfMousePos) && loadLevelEntryName.m_bIsEntering == true)
				{

					loadLevelEntryName.m_bIsEntering = false;
					play(loadLevelEntryName.m_sText);
					window.close();
					gameView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
				}
				else if (QuitButton.m_bClicked(sfMousePos))
				{
					window.close();
					playMenu();
				}
			}
		}
		window.clear(Color::Black);



		//draw the hud
		window.setView(hudView);

		window.draw(QuitButton);

		if (loadLevelEntryName.m_bIsEntering)
		{
			window.draw(listOfProfilesSprite);
			window.draw(loadLevelEntryName);
			window.draw(loadSubmitButton);
		}


		//show the window
		window.display();
	}

	
}

void editor()
{
	//Game Object
	Game Editor;
	Editor = Game("editor");

	//Create a window with the specifications of the profile
	RenderWindow window;
	if (player->m_bFullscreen == true) window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Editor", Style::Fullscreen);
	else window.create(VideoMode(player->m_sfResolution.x, player->m_sfResolution.y), "Editor");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//create a view to fill the windowfor game render
	View gameView;
	gameView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	gameView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
	gameView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	//create a view to fill the windowfor game render
	View hudView;
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	hudView.setCenter(sf::Vector2f(player->m_sfResolution.x / 2, player->m_sfResolution.y / 2));
	hudView.setSize(sf::Vector2f(player->m_sfResolution.x, player->m_sfResolution.y));

	//helps scale hud elements
	Vector2f resolutionScale(player->m_sfResolution.x / 1280, player->m_sfResolution.y / 720);
	Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
	Vector2f middleOfScreen((player->m_sfResolution.x / 2) - (buttonSize.x / 2), (player->m_sfResolution.y / 2) - (buttonSize.y / 2));

	//create Buttons for the editor---------------------------------
	Button BackgroundButton
	("Background",
		Vector2f(0, 0),
		Vector2f(300 * resolutionScale.x , 88.5 * resolutionScale.y) ,
		resolutionScale,
		"Button_Green"
		);
	Button SizeButton
	("Level Size",
		Vector2f(0, 90 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);

	Button TimeButton
	("Time of Day",
		Vector2f(0, 180 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);

	Button RoadSelectorButton
	("Roads",
		Vector2f(0, 270 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);

	Button twoWayButton
	("Two Way Road",
		Vector2f(300 * resolutionScale.x, 120 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button TJunctionButton
	("T - Junction",
		Vector2f(300 * resolutionScale.x, 210 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button CrossRoadsButton
	("Cross Roads",
		Vector2f(300 * resolutionScale.x, 300 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button CornerButton
	("Corner",
		Vector2f(300 * resolutionScale.x, 390 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);

	Button trafficLightButton
	("Lights",
		Vector2f(0, 360 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);

	Button normalLightButton
	("Traffic Lights",
		Vector2f(300 * resolutionScale.x, 315 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button pedLightButton
	("Pedestrian Lights",
		Vector2f(300 * resolutionScale.x, 405 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);

	Button unitsButton
	("units",
		Vector2f(0, 450 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button lessunitsButton
	("-",
		Vector2f(300 * resolutionScale.x, 450 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button numberunitsButton
	(" ",
		Vector2f(550 * resolutionScale.x, 450 * resolutionScale.y),
		Vector2f(250 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button moreunitsButton
	("+",
		Vector2f(800 * resolutionScale.x, 450 * resolutionScale.y),
		Vector2f(250 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button pedsButton
	("Pedestrians",
		Vector2f(0, 540 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button lessPedsButton
	("-",
		Vector2f(300 * resolutionScale.x, 540 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button numberPedsButton
	(" ",
		Vector2f(550 * resolutionScale.x, 540 * resolutionScale.y),
		Vector2f(250 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button morePedsButton
	("+",
		Vector2f(800 * resolutionScale.x, 540 * resolutionScale.y),
		Vector2f(250 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button StartEndPointsButton
	("Start/End Points",
		Vector2f(0, 630 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button startPointButton
	("Start Point",
		Vector2f(300 * resolutionScale.x, 630 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 44.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);
	Button endPointButton
	("End Point",
		Vector2f(300 * resolutionScale.x, 675 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 44.5 * resolutionScale.y),
		resolutionScale,
		"Button_Yellow"
	);



	//Menu Buttons-------------------------------------------------
	Button newButton
	("New",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, 0),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button saveButton
	("Save",
		Vector2f( player->m_sfResolution.x - 300 * resolutionScale.x, 90 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button loudButton
	("Load",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, 180 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button helpButton
	("Help",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, 270 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);
	Button pathfinding
	("Grid",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, 360 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);

	Button QuitButton
	("Exit",
		Vector2f(player->m_sfResolution.x - 300 * resolutionScale.x, player->m_sfResolution.y - 90 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		resolutionScale,
		"Button_Green"
	);

	//Enter you level Sprite
	RectangleShape listOfProfilesRect;
	Sprite listOfProfilesSprite;
	Texture listOfProfilesTex;
	if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenu.png"))
	{
		cout << "Error: ProfileEnterBackground.png was unable to load.";
	};
	listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x, -120 + middleOfScreen.y * resolutionScale.y));
	listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
	listOfProfilesRect.setFillColor(Color::Blue);

	listOfProfilesSprite.setTexture(listOfProfilesTex);
	listOfProfilesSprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
	listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());


	//create text box 
	Vector2f edgeOfTextBox(listOfProfilesRect.getPosition().x, listOfProfilesRect.getPosition().y + (144 * resolutionScale.y) / 2);
	TextBox saveLevelEntryName("Enter level name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
	TextBox loadLevelEntryName("Enter level name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");

	Button saveSubmitButton("Submit", Vector2f(edgeOfTextBox.x + 343, edgeOfTextBox.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5),  resolutionScale, "Button_Green");
	Button loadSubmitButton("Submit", Vector2f(edgeOfTextBox.x + 343, edgeOfTextBox.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5),  resolutionScale, "Button_Green");
	
	//help screen
	Overlay helpOverlayMessage(Vector2f(200 * resolutionScale.x,150 * resolutionScale.y), Vector2f(888 * resolutionScale.x, 500 * resolutionScale.y),
		"This is the level editor\n\n-You can move around with W,A,S,D\n-Zoom in and out with the mouse wheel\n-Interact with the buttons with left mouse\n\nOnce an you have selected an object for placement : \n - Place it with enter\n - Cancel with Right mouse\n\nPress Help to veiw this message again");

	helpOverlayMessage.m_bDraw = true;

	float fRotation = 0;

	//selection string
	string sType; // type of object been placed by the editor

	//input delay
	Clock inputDelay;

	//bool for when the player is using the menu button
	bool usingMenu = true; // true when using buttons (stops un wanted interaction)

	while (window.isOpen())
	{
		//handle input
		Event event;
		Vector2f sfMousePos;
		Vector2f sfPlacingPos;
		int iMouseWheel;

		Time elapsedTime = inputDelay.getElapsedTime();

		if (elapsedTime.asMilliseconds() >= 100.0f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				fRotation -= 90;
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				fRotation += 90;
			}

			if (fRotation >= 360)fRotation = 0;
			if (fRotation < 0)fRotation = 270;
			inputDelay.restart();
			
		}
		
		if (!usingMenu)
		{
			//move camera
			float fMoveSpeed = 10;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				fMoveSpeed *= 3;
			}
			//key presses
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				gameView.move(Vector2f(0.0f, -fMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				gameView.move(Vector2f(0.0f, fMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				gameView.move(Vector2f(-fMoveSpeed, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				gameView.move(Vector2f(fMoveSpeed, 0.0f));
			}


			//move the editor objects
			sfPlacingPos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);
			

		

		}	

		while (window.pollEvent(event))
		{

			sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);
			
				
			if (event.type == Event::MouseWheelMoved)
			{
				iMouseWheel= event.mouseWheel.delta;
				if (iMouseWheel > 0)
				{
					//zoom in
					gameView.zoom(0.9);
				}
				if (iMouseWheel < 0)
				{
					//zoom out
					gameView.zoom(1.1);
				}
			}

			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return;
			}
			if (event.type == sf::Event::KeyPressed && saveLevelEntryName.m_bIsEntering == true)
			{
				saveLevelEntryName.takeInput(event.key.code);
			}
			if (event.type == sf::Event::KeyPressed && loadLevelEntryName.m_bIsEntering == true)
			{
				loadLevelEntryName.takeInput(event.key.code);
			}
			

		}

		window.clear(Color::Black);

		//draw the game 
		window.setView(gameView);
		
		Editor.updateScene(0.01f);
		Editor.drawScene(window);

		//draw the hud
		window.setView(hudView);

		if (!placingBool && !usingMenu)
		{

			window.draw(BackgroundButton);
			window.draw(SizeButton);
			window.draw(TimeButton);
			window.draw(RoadSelectorButton);
			window.draw(trafficLightButton);
			window.draw(unitsButton);
			window.draw(pedsButton);
			window.draw(StartEndPointsButton);
			

			if (RoadSelectorBool)
			{
				window.draw(twoWayButton);
				window.draw(TJunctionButton);
				window.draw(CrossRoadsButton);
				window.draw(CornerButton);
			}
			if (LightSelectorBool)
			{
				window.draw(normalLightButton);
				window.draw(pedLightButton);
			}
			if (unitsSelectorBool)
			{
				window.draw(lessunitsButton);
				window.draw(numberunitsButton);
				window.draw(moreunitsButton);
			}
			if (PedSelectorBool)
			{
				window.draw(lessPedsButton);
				window.draw(numberPedsButton);
				window.draw(morePedsButton);
			}
			if (StartEndPointsBool)
			{
				window.draw(startPointButton);
				window.draw(endPointButton);
			}

			window.draw(newButton);
			window.draw(saveButton);
			window.draw(loudButton);
			window.draw(helpButton);
			window.draw(pathfinding);
			window.draw(QuitButton);
			window.draw(helpOverlayMessage);
		
		}
		if (usingMenu)
		{
			window.draw(helpOverlayMessage);
			
			if (saveLevelEntryName.m_bIsEntering)
			{
				window.draw(listOfProfilesSprite);
				window.draw(saveLevelEntryName);
				window.draw(saveSubmitButton);
			}
			if (loadLevelEntryName.m_bIsEntering)
			{
				window.draw(listOfProfilesSprite);
				window.draw(loadLevelEntryName);
				window.draw(loadSubmitButton);
			}
			
		
		}
		
		//show the window
		window.display();
		
	}

}

void resetSelectors()
{
	RoadSelectorBool = false;
	LightSelectorBool = false;
	unitsSelectorBool = false;
	PedSelectorBool = false;
	StartEndPointsBool = false;

	placingBool = false; 
}
