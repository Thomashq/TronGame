#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//compilando shaders
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	} 
)";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	//Setup  do tamanho da janela
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Tron Game CG", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//criação do vertex object, representado por um ID
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//compila o objeto do shader que já foi associado ao shader source anterioremente
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//FragmentShaders cuida da renderização de cores na tela, as configurações dele vão calcular o pixel output de cores dos pixels
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//o Shader Program vai linkar diferentes shader objects e criar um grande shader combinado
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//Junta os shaders pelo glAtach e link pelo glLink
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Ativa os resultados do shaderprogram que foi linkado
	glUseProgram(shaderProgram);

	//Uma vez que esses shaders foram linkados no shader program, não há mais necessidade de guardar o vertex e o fragment, logo, é boa prática deletar
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Os Vertex Shaders são estruturas versáteis, qyualquer input pode ser representado como um vertex attribute, permite flexibilidade, mas é preciso especificar como o OpenGL deve interpretar esses atributos
	//a função glVertexAttribPointer, especifica como essa interpretação será feita
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	//agora é necessário ativar os vertex attributes
	//Setup VBO Gerador de buffers para armazenar na GPU, criar fora do laço de janela, porque ficará armazenado na memória constantemente enquanto houver espaço.
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configurações da janela
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//Podem haver multiplas VBOs para chamadas de novos objetos
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//salvar vertex atributes como ponteiros é bom, porque só é preciso fazer a chamada uma vez, após isso apenas é necessário bindar o correto VAO
	//seta os vertex attributes como ponteiros
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glUseProgram(shaderProgram);

	//guarda o VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//laço que mantem a janela do jogo rodando (igual fup)
	while (!glfwWindowShouldClose(window))
	{
		//Processa os Inputs(Culpa do Pedro)
		processInput(window);
		//informações de renderização
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Controle de entradas e buffers
		glfwSwapBuffers(window);//Faz a troca dos Buffers que vão desenhar os elementos na tela
		glfwPollEvents();//Controla as entradas do teclado e mouse.
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
	}
	glfwTerminate();
	return 0;
}
//Faz o remensionamento do contexto OpenGL de acordo com a janela e interação do usuário
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}