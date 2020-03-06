#include "SFML\Graphics.hpp"
#include <random>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int FRAME_RATE = 60;
const int ARRAY_SIZE = 50;

// Width adjusted with respected to the window width and array size in order to fit the screen
const float RECTANGLE_WIDTH = (float)WINDOW_WIDTH / ARRAY_SIZE;

// Height adjusted with respect to window height and array size in order to fit half the screen
const float HEIGHT_STEP = ((float)WINDOW_HEIGHT / 2) / ARRAY_SIZE;

// Function prototypes declared which will be used for array sorting
void swapArrayIndices(float *array, int x, int y);

void quickSort(float *array, int start, int end);

int partition(float *array, int start, int end);

int main()
{
	srand(time(NULL));

	// Create an array with randomly set heights from 1-50 times the height step
	// Nested loop will check if each new height is different than the current height of each element in the array
	float heightArray[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		heightArray[i] = 0.0;
	}

	int index = 0;
	while (index < ARRAY_SIZE)
	{
		float height = (rand() % ARRAY_SIZE + 1) * HEIGHT_STEP;
		bool isNewHeight;

		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			if (height == heightArray[i])
			{
				isNewHeight = false;
				break;
			}
			else
			{
				isNewHeight = true;
			}
		}

		if (isNewHeight)
		{
			heightArray[index] = height;
			index++;
		}
	}

	// Create a copy of the array that will stay unsorted
	float copyArray[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		copyArray[i] = heightArray[i];
	}

	// Sort original array 
	quickSort(heightArray, 0, ARRAY_SIZE - 1);

	// Load font
	sf::Font font;
	font.loadFromFile("OpenSans-Bold.ttf");

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "QuickSort");
	window.setFramerateLimit(FRAME_RATE);

	while (window.isOpen())
	{
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Clear window
		window.clear();

		// Draw objects

		// Compare original array to coppied array
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			sf::RectangleShape unSortedRectangleArray;
			unSortedRectangleArray.setPosition(RECTANGLE_WIDTH * i, (WINDOW_HEIGHT / 2) - copyArray[i]);
			unSortedRectangleArray.setSize(sf::Vector2f(RECTANGLE_WIDTH - 1, copyArray[i] - 1));
			unSortedRectangleArray.setOutlineColor(sf::Color::Black);
			unSortedRectangleArray.setOutlineThickness(1);
			window.draw(unSortedRectangleArray);

			sf::RectangleShape sortedRectangleArray;
			sortedRectangleArray.setPosition(RECTANGLE_WIDTH * i, WINDOW_HEIGHT - heightArray[i]);
			sortedRectangleArray.setSize(sf::Vector2f(RECTANGLE_WIDTH - 1, heightArray[i] - 1));
			sortedRectangleArray.setOutlineColor(sf::Color::Black);
			sortedRectangleArray.setOutlineThickness(1);
			window.draw(sortedRectangleArray);
		}

		// Text to label unsorted and sorted array
		sf::Text unSortedRectangleText("Unsorted Array", font);
		unSortedRectangleText.setPosition(WINDOW_WIDTH * 0.40, 0);
		unSortedRectangleText.setFillColor(sf::Color::White);
		unSortedRectangleText.setOutlineThickness(2);
		window.draw(unSortedRectangleText);

		sf::Text sortedRectangleText("Sorted Array", font);
		sortedRectangleText.setPosition(WINDOW_WIDTH * 0.42, WINDOW_HEIGHT / 2);
		sortedRectangleText.setFillColor(sf::Color::White);
		sortedRectangleText.setOutlineThickness(2);
		window.draw(sortedRectangleText);
		
		window.display();
	}

	return 0;
}


// Simple array element swap function that will be used in the partition function
void swapArrayIndices(float *array, int x, int y)
{
	float temp;
	temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

// Recursive function used for sorting
void quickSort(float *array, int start, int end)
{
	if (start < end)
	{
		int partitionIndex = partition(array, start, end);

		quickSort(array, start, partitionIndex - 1);
		quickSort(array, partitionIndex + 1, end);
	}
}

// Partition function will start with a given pivot index
// Each value smaller than the value in the pivot index will be placed to the left of it
// Each value greater than the value in the pivot index will be placed to the right of it
int partition(float *array, int start, int end)
{
	int pivotIndex = start;
	float pivotValue = array[end];

	for (int i = start; i < end; i++)
	{
		if (array[i] < pivotValue)
		{
			swapArrayIndices(array, i, pivotIndex);
			pivotIndex++;
		}
	}

	swapArrayIndices(array, pivotIndex, end);

	return pivotIndex;
}
