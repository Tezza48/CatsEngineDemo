#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include <stb/stb_image.h>
#include <cstdio>
#include <vector>
#include <GL/glew.h>    // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "SpriteSheet.h"
#include <fstream>

void OnGui();

bool OpenTexture(const char * filename);
void OpenSprites(const char * filename);
void SaveSprites(const char * filename);
bool SerializeSprites(void * data, int idx, const char ** outData);

GLFWwindow * window;
int windowWidth = 1280, windowHeight = 720;
GLuint tex;

std::vector<Sprite> sprites(1);
int currentSpriteIndex;

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
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsLight();

	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	OpenTexture("environment-desert.png");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		OnGui();
		ImGui::Render();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(3.0f, 3.0f, 3.0f, 1.0f);

		glMatrixMode(GL_PROJECTION_MATRIX);

		float aspect = static_cast<float>(windowWidth) / windowHeight;

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
	static bool showDemoWindow = false;

	float mainMenubarHeight;
	{// Main Menubar
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit")) glfwSetWindowShouldClose(window, true);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			//if (ImGui::ShowStyleSelector("Style")) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Show Demo Window", &showDemoWindow);
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

		mainMenubarHeight = ImGui::GetWindowHeight();
		ImGui::EndMainMenuBar();
	}

	if(currentSpriteIndex >= 0)
	{// Editor View (Background)
		ImGui::SetNextWindowPos(ImVec2(0, mainMenubarHeight));
		ImGui::SetNextWindowSize(ImVec2((float)windowWidth, windowHeight - mainMenubarHeight));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::Begin("Editor", nullptr, 
			ImGuiWindowFlags_NoTitleBar | 
			//ImGuiWindowFlags_NoBackground | 
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize);


		const float maxImageWidth = 500.0f;
		float imageSize = ImGui::GetContentRegionAvail().y;
		ImVec2 imageStart = ImGui::GetCursorScreenPos();
		ImGui::Image((void *)tex, ImVec2(imageSize, imageSize));
		
		// Settings on the Right or Below
		{
			ImGui::SameLine();
			ImGui::BeginChild("Rect Tools", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::Text("Sprite Rect: x, y, width, height.");
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat4("##RectSliders", sprites[currentSpriteIndex].rect.data(), 0.0f, 1.0f);
				ImGui::InputFloat4("##RectInputs", sprites[currentSpriteIndex].rect.data(), 4);
				ImGui::PopItemWidth();
			}
			ImGui::NewLine();
			ImGui::ColorEdit4("Color", sprites[currentSpriteIndex].color.data());
			const float previewWidth = ImGui::GetItemRectSize().x;
			ImVec2 size = ImVec2(previewWidth, previewWidth * sprites[currentSpriteIndex].rect[3] / sprites[currentSpriteIndex].rect[2]);
			ImVec2 uvA = ImVec2(sprites[currentSpriteIndex].rect[0], sprites[currentSpriteIndex].rect[1]);
			ImVec2 uvB = ImVec2(uvA.x + sprites[currentSpriteIndex].rect[2], uvA.y + sprites[currentSpriteIndex].rect[3]);
			ImGui::Image((void *)tex, size, uvA, uvB, ImVec4(sprites[currentSpriteIndex].color[0], sprites[currentSpriteIndex].color[1], sprites[currentSpriteIndex].color[2], sprites[currentSpriteIndex].color[3]));
			ImGui::EndChild();
		}


		ImVec2 rectStartPos = ImVec2(imageStart.x + sprites[currentSpriteIndex].rect[0] * imageSize, imageStart.y + sprites[currentSpriteIndex].rect[1] * imageSize);
		ImVec2 rectEndPos = ImVec2(rectStartPos.x + sprites[currentSpriteIndex].rect[2] * imageSize, rectStartPos.y + sprites[currentSpriteIndex].rect[3] * imageSize);
		auto * drawList = ImGui::GetWindowDrawList();
		{
			ImGui::PushClipRect(imageStart, ImVec2(imageStart.x + imageSize, imageStart.y + imageSize), true);
			drawList->AddRectFilled(rectStartPos, rectEndPos, ImColor(0.3f, 1.0f, 0.3f, 0.3f));
			drawList->AddRect(rectStartPos, rectEndPos, ImColor(0.2f, 1.0f, 0.2f, 1.0f));
			ImGui::PopClipRect();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

	{
		ImGui::Begin("Sprite Selector");
		if (ImGui::Button("Add"))
		{
			sprites.emplace_back();
			currentSpriteIndex = sprites.size() - 1;
		}

		if (currentSpriteIndex >= 0)
		{
			ImGui::SameLine(); 
			if (ImGui::Button("Remove"))
			{
				sprites.erase(sprites.begin() + currentSpriteIndex);
				currentSpriteIndex--;
			}
		}
		ImGui::ListBox("Sprites", &currentSpriteIndex, &SerializeSprites, sprites.data(), sprites.size(), 16);
		ImGui::End();
	}

	if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

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

void OpenSprites(const char * filename)
{

}

void SaveSprites(const char * filename)
{

}

bool SerializeSprites(void * data, int idx, const char ** outData)
{
	std::string *name = new std::string("Sprite " + std::to_string(idx));
	*outData = name->c_str();
	return true;
}
