#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include <stb/stb_image.h>
#include <cstdio>

#include <GL/glew.h>    // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "SpriteSheet.h"

void OnGui();

bool OpenTexture(const char * filename);

static GLFWwindow * window;
static int windowWidth = 1600, windowHeight = 900;
GLuint tex;

SpriteSheet * sheet;

int main(int argc, char ** argv)
{
	if (!glfwInit())
	{
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwSwapInterval(1);

#if DEBUG || _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	window = glfwCreateWindow(windowWidth, windowHeight, "Sprite Editor", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	ImGui::CreateContext();
	ImGuiIO & io = ImGui::GetIO();
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	sheet = new SpriteSheet();
	sheet->texName = "environment-desert.png";
	OpenTexture("environment-desert.png");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		OnGui();
		ImGui::Render();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		//glMatrixMode(GL_PROJECTION_MATRIX);

		//float aspect = static_cast<float>(windowWidth) / windowHeight;

		//glBegin(GL_QUADS);
		//glColor3f(1, 1, 1);
		//glVertex2f(-aspect, -1);
		//glVertex2f(aspect, -1);
		//glVertex2f(aspect, 1);
		//glVertex2f(-aspect, 1);
		//glEnd();

		//glBegin(GL_TRIANGLES);
		//glColor3f(1, 0, 0);
		//glVertex2f(-0.5f, -0.5f);
		//glColor3f(0, 1, 0);
		//glVertex2f(0.0f, 0.5f);
		//glColor3f(0, 0, 1);
		//glVertex2f(0.5f, -0.5f);
		//glEnd();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void OnGui()
{
	static bool showOpenDialog = false;
	{
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				if(sheet) delete sheet;
				sheet = new SpriteSheet();
			}
			//showOpenDialog = ImGui::MenuItem("Open");

			//showOpenDialog = ImGui::MenuItem("Open");
			ImGui::EndMenu();
		}

		//if (showOpenDialog)
		//{
		//	ImGui::Begin("Open");
		//	char filename[512]{ 0 };
		//	ImGui::InputText("Filename", filename, 512);
		//	if (ImGui::Button("Submit"))
		//	{
		//		bool LoadTexture(filename);
		//		showOpenDialog = false;
		//	}
		//	ImGui::End();
		//}

		if (ImGui::MenuItem("Quit")) glfwSetWindowShouldClose(window, true);
		ImGui::EndMainMenuBar();
	}

	static bool showDemoWindow = true;
	if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);
	
	{
		ImGui::Begin("Editor");

		static int currentItem;
		//const char ** items = new char*[sheet->sprites.size()];
		//for (size_t i = 0; i < sheet->sprites.size(); i++)
		//{
		//	items[i] = "sprite " + (i+1);
		//}

		//ImGui::ListBox("Sprites", &currentItem, items, sheet, sheet->sprites.size());
		//if (ImGui::Button("Add")) sheet->sprites.emplace_back();
		ImGui::Image((void *)tex, ImVec2(ImGui::GetItemRectMax().x - ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().x - ImGui::GetItemRectMin().x));
		ImGui::End();
	}
}

bool OpenTexture(const char * filename)
{
	int x, y, n;
	unsigned char * data = stbi_load(filename, &x, &y, &n, 4);
	if (!data) return false;
	fprintf(stderr, stbi_failure_reason());
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return true;
}
