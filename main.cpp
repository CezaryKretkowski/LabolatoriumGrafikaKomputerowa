#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "dependeces/Common/Initialize.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#include "dependeces/Common/shader.hpp"
#include "dependeces/Common/controls.hpp"
#include "src/objLoader.h"
#include "src/Object.h"
#include "src/Task1.h"
#include "src/Task2.h"

int main()
{
    Task1 *task = new Task1();
    task->run();

    return 0;
}
