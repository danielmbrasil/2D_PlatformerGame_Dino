#include "TextureManager.h"
#include "../vendor/tinyxml/tinyxml.h"
#include <iostream>

TextureManager *TextureManager::s_Instance = nullptr;

bool TextureManager::loadTexture(const std::string &id, const std::string &filename) {
    surface = IMG_Load(filename.c_str());

    if (!surface) {
        SDL_Log("Failed to load surface: %s\n", SDL_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("Failed to load texture: %s\n", SDL_GetError());
        return false;
    }

    texturesMap[id] = texture;

    return true;
}

void
TextureManager::draw(const std::string &id, int x, int y, int width, int height, SDL_RendererFlip flip, float scale) {
    srcRect = {0, 0, width, height};
    camera = Camera::getInstance()->getPosition();
    destRect = {static_cast<int>((float) x - camera.x), static_cast<int>((float) y - camera.y),
                (int) ((float) width * scale), (int) ((float) height * scale)};

    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void
TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame, int scale,
                          SDL_RendererFlip flip) {
    srcRect = {width * frame, height * row, width, height};
    camera = Camera::getInstance()->getPosition();
    destRect = {static_cast<int>((float) x - camera.x), static_cast<int>((float) y - camera.y), width * scale,
                height * scale};
    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawTile(const std::string &tilesetID, int tileSize, int x, int y, int row, int frame,
                              SDL_RendererFlip flip) {
    camera = Camera::getInstance()->getPosition();
    destRect = {static_cast<int>((float) x - camera.x), static_cast<int>((float) y - camera.y), tileSize, tileSize};
    srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::parseTexture(const std::string &src) {
    TiXmlDocument xml;
    xml.LoadFile(src);

    if (xml.Error()) {
        std::cerr << "Failed to load file: " << src << std::endl;
        return;
    }

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("texture")) {
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            loadTexture(id, source);
        }
    }
}

void TextureManager::drop(const std::string &id) {
    SDL_DestroyTexture(texturesMap[id]);
    texturesMap.erase(id);
}

void TextureManager::clean() {
    std::map<std::string, SDL_Texture *>::iterator iterator;

    for (iterator = texturesMap.begin(); iterator != texturesMap.end(); iterator++)
        SDL_DestroyTexture(iterator->second);

    texturesMap.clear();

    SDL_Log("Texture map cleaned.");
}
