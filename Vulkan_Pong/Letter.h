#pragma once
#include "Object.h"

enum TitleLetterEnum {
    P = 'p',
    O = 'o',
    N = 'n',
    G = 'g'
};

class Letter :
    public Object
{
private:
    glm::vec3 pos;
    glm::vec2 scale;
    std::vector<glm::vec3> vertexColors;

    TitleLetterEnum titleLetterEnum;

    void updateVertices() override;

public: 

    Letter(TitleLetterEnum titleLetter);
    Letter(TitleLetterEnum titleLetter, glm::vec3 pos);
    Letter(TitleLetterEnum titleLetter, glm::vec3 pos, glm::vec2 scale);

    // Getters
    glm::vec3 getPos() const { return pos; }
    std::vector<glm::vec3> GetVertexColors() const { return vertexColors; }

    // Setters
    void setPos(glm::vec3 newPos) { pos = newPos; }
    void setVertexColors(std::vector<glm::vec3> newVertexColors)
    {
        vertexColors.clear();
        vertexColors = newVertexColors;
    }

    void setVertexColors(glm::vec3 newVertexColor);

    void initialize() override;
    void render() override;
    void behave(float deltaTime) override;
};

