#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

class TextureManager {
public:
	sf::Texture& getTexture(const std::string& filename) {
		auto it = textures.find(filename);
		if (it != textures.end()) {
			return it->second;
		}

		sf::Texture texture;
		if (!texture.loadFromFile(filename)) {
			throw std::runtime_error("Failed to load texture: " + filename);
		}

		textures[filename] = std::move(texture);
		return textures[filename];
	}


	void clear() {
		textures.clear();
	}


private:
	std::map<std::string, sf::Texture> textures;
};