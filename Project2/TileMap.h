#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
	{

		//loading the tileset textures
		if (!m_tileset.loadFromFile(tileset))
			return false;

		//resize array to fit level siez
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		//populate vertex array
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				//get current tile number
				int tileNum = tiles[i + j * width];

				//find its position in the tileset texture
				int tu = tileNum % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNum / (m_tileset.getSize().x / tileSize.x);

				//get pointer to current tiles quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				//define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}
		return true;
	}

	int getTileAtPosition(int x, int y, const int* level, int rowSize)
	{
		int index = y * rowSize + x;
		return level[index];
	}

	bool drawGrid(sf::RenderWindow& window, int shapeSize, unsigned int numRows, unsigned int numCols) {
		sf::RectangleShape grid(sf::Vector2f(shapeSize, shapeSize));
		grid.setFillColor(sf::Color::Transparent);  // No fill for grid lines
		grid.setOutlineColor(sf::Color::White);     // White outline for the grid
		grid.setOutlineThickness(1.0f);             // Adjust thickness if necessary

		// Loop through each cell in the grid
		for (unsigned int row = 0; row < numRows; ++row) {
			for (unsigned int col = 0; col < numCols; ++col) {
				// Set the position of the grid cell
				grid.setPosition(col * shapeSize, row * shapeSize);
				window.draw(grid);  // Draw the cell on the window
			}
		}
		return true;
	}

private: 
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		//apply the transform
		states.transform *= getTransform();
		//apply the tileset texture
		states.texture = &m_tileset;

		//draw the array
		target.draw(m_vertices, states);
	}
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;
};

