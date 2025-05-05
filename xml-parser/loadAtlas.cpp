#include "loadAtlas.h"
#include "pugixml.hpp"
#include "../headers/exceptions.h"

std::map<std::string, spriteData> parseTextureAtlasPugi(const std::string &xmlPath) {
    pugi::xml_document doc;
    std::string outTextureFilename;
    std::map<std::string, spriteData> resultMap;
    outTextureFilename.clear();

    pugi::xml_parse_result result = doc.load_file(xmlPath.c_str());
    if (!result) {
        std::string errorMsg = "PugiXML Error: Failed to load/parse '" + xmlPath +
                               "'. Description: " + result.description() +
                               " (Offset: " + std::to_string(result.offset) + ")";
        throw AssetException(errorMsg); // THROW exception on failure
    }
    std::cout << "Successfully loaded XML: " << xmlPath << std::endl;


    pugi::xml_node textureAtlasNode = doc.child("TextureAtlas");
    if (!textureAtlasNode) {
        throw AssetException("XML Error: Could not find <TextureAtlas> root element in '" + xmlPath + "'"); // THROW
    }


    pugi::xml_attribute imagePathAttr = textureAtlasNode.attribute("imagePath");
    if (!imagePathAttr) {
        throw AssetException("XML Error: <TextureAtlas> node missing 'imagePath' attribute in '" + xmlPath +
                                 "'"); // THROW
    }

    outTextureFilename = imagePathAttr.as_string();
    if (outTextureFilename.empty()) {

        std::cerr << "Warning: 'imagePath' attribute is empty in '" << xmlPath << "'" << std::endl;
    }
    std::cout << "Texture Atlas image file specified: " << outTextureFilename << std::endl;

    int count = 0;
    for (pugi::xml_node subTextureNode: textureAtlasNode.children("SubTexture")) {

        pugi::xml_attribute nameAttr = subTextureNode.attribute("name");
        pugi::xml_attribute xAttr = subTextureNode.attribute("x");
        pugi::xml_attribute yAttr = subTextureNode.attribute("y");
        pugi::xml_attribute widthAttr = subTextureNode.attribute("width");
        pugi::xml_attribute heightAttr = subTextureNode.attribute("height");
        pugi::xml_attribute frameXAttr = subTextureNode.attribute("frameX");
        pugi::xml_attribute frameYAttr = subTextureNode.attribute("frameY");
        pugi::xml_attribute frameWidthAttr = subTextureNode.attribute("frameWidth");
        pugi::xml_attribute frameHeightAttr = subTextureNode.attribute("frameHeight");


        if (!nameAttr || !xAttr || !yAttr || !widthAttr || !heightAttr || !frameXAttr || !frameYAttr || !frameWidthAttr || !frameHeightAttr) {
            std::string missingName = nameAttr ? nameAttr.as_string("<NO NAME ATTR>") : "<NAME MISSING>";
            std::cerr << "Warning: Skipping <SubTexture> '" << missingName
                      << "' due to missing required attributes in '" << xmlPath << "'" << std::endl;
            continue; // Skip this SubTexture
        }


        std::string name = nameAttr.as_string();
        int x = xAttr.as_int();
        int y = yAttr.as_int();
        int width = widthAttr.as_int();
        int height = heightAttr.as_int();
        int frameX = frameXAttr.as_int();
        int frameY = frameYAttr.as_int();
        int frameWidth = frameWidthAttr.as_int();
        int frameHeight = frameHeightAttr.as_int();

        if (width <= 0 || height <= 0) {
            std::cerr << "Warning: Skipping SubTexture '" << name << "' due to invalid dimensions (" << width << "x"
                      << height << ") in '" << xmlPath << "'" << std::endl;
            continue;
        }

        spriteData data;
        data.set_texture_rect(sf::IntRect({x, y}, {width, height}));

        resultMap[name] = spriteData(x, y, width, height, frameX, frameY, frameWidth, frameHeight);
        count++;
    }


    std::cout << "Successfully parsed " << count << " <SubTexture> elements." << std::endl;

    return resultMap;
}

