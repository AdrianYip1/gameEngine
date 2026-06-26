#pragma once

#include "stb_image.h"
#include <string>
#include <iostream>

struct Texture {
	unsigned int texture; // the ID
    std::string type;
    std::string path;
	int w, h, nrChannels;
public:
	Texture(const char* path, std::string _type) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char* data = stbi_load(path, &w, &h, &nrChannels, 0);

        if (data) {
            GLenum format = GL_RGB;
            if (nrChannels == 1) format = GL_RED;
            else if (nrChannels == 3) format = GL_RGB;
            else if (nrChannels == 4) format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            this->type = _type;
        }
        else {
            std::cout << "ERROR loading texture: " << path << std::endl;
        }
        stbi_image_free(data);
	}

    ~Texture() { glDeleteTextures(1, &texture); }

    // Can't copy textures
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& o) noexcept :
        texture(o.texture), w(o.w), h(o.h), nrChannels(o.nrChannels), type(std::move(o.type)), path(std::move(o.path)) {
        o.texture = o.w = o.h = o.nrChannels = 0;
    }

    Texture& operator=(Texture&& o) noexcept {
        if (this != &o) {
            glDeleteTextures(1, &texture);
            texture = o.texture;
            w = o.w;
            h = o.h;
            nrChannels = o.nrChannels;
            type = std::move(o.type);
            path = std::move(o.path);
            o.texture = o.w = o.h = o.nrChannels = 0;
        }
        return *this;
    }


    void bind(unsigned int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};