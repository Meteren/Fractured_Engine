
#include <glad/glad.h>
#include <Window.h>
#include <SDL.h>
#include <essentials/ShaderLoader.h>

int main(int argc, char* argv[]) {
	
	bool running = true;

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)){
		printf("SDL Init is failed: %s\n", SDL_GetError());
		return -1;
	}

	if (!SDL_GL_LoadLibrary(NULL)) {
		printf("SDL Gl library load is failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);


	FRACTURED_WINDOW::Window window = FRACTURED_WINDOW::Window("Engine Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_OPENGL);

	if (!window.GetWindow()) {
		printf("Window can't be created.\n");
		return -1;
	}

	if (!window.setGLContext())
		return -1;

	SDL_GL_MakeCurrent(window.GetWindow().get(), window.GetGLContext());

	SDL_GL_SetSwapInterval(1);

	if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
		printf("Glad can't be loaded.\n");
		return -1;
	}

	float vertices[] = {
		  //vertices		   //uvs	
		-0.5f, 0.5f,0.0f,   0.0f, 1.0f, // 0
		 0.5f, 0.5f,0.0f,   1.0f, 1.0f,// 1
		-0.5f, -0.5f,0.0f,  0.0f, 0.0f,// 2
		 0.5f,-0.5f,0.0f,   1.0f, 0.0f// 3

	};

	unsigned int indices[] = {
		0,1,3,
		3,2,0
	};

	//Creating buffers in here -- later will be replaced with a proper buffer class and a vertex struct

	auto shader = FRACTURED_RENDERING::ShaderLoader::createShader("C:/Users/Meate/source/repos/Fractured_Engine/FRACTURED_EDITOR/assets/shaders/vertex.shader",
		"C:/Users/Meate/source/repos/Fractured_Engine/FRACTURED_EDITOR/assets/shaders/fragment.shader");

	unsigned int VAO;

	unsigned int EBO;

	unsigned int VBO;

	glCreateVertexArrays(1,&VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//---
	
	glViewport(0, 0, window.GetWidth(), window.GetHeight());
	
	SDL_Event event{};

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE)
					running = false;
				break;
			default:
				break;

			}	

		}
		
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw here

		glBindVertexArray(VAO);

		shader.get()->useShaderProgram();

		shader.get()->setFloat4("u_color", 0, 0, 1, 1);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);

		glUseProgram(0);
		

		SDL_GL_SwapWindow(window.GetWindow().get());
	}

	return 0;


}