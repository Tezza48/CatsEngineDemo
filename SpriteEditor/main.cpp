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

		glMatrixMode(GL_PROJECTION_MATRIX);

		float aspect = static_cast<float>(windowWidth) / windowHeight;

		glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(-aspect, -1);
		glVertex2f(aspect, -1);
		glVertex2f(aspect, 1);
		glVertex2f(-aspect, 1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0, 1, 0);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0, 0, 1);
		glVertex2f(0.5f, -0.5f);
		glEnd();

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

		

		//static int currentItem;
		//const char ** items = new char*[sheet->sprites.size()];
		//for (size_t i = 0; i < sheet->sprites.size(); i++)
		//{
		//	items[i] = "sprite " + (i+1);
		//}

		//ImGui::ListBox("Sprites", &currentItem, items, sheet, sheet->sprites.size());
		//if (ImGui::Button("Add")) sheet->sprites.emplace_back();
		const float maxImageWidth = 500.0f;
		float imageSize = fmin(ImGui::GetItemRectSize().x, maxImageWidth);
		imageSize = (ImGui::GetItemRectSize().x / 3) * 2;
		ImVec2 imageStart = ImGui::GetCursorScreenPos();
		ImGui::Image((void *)tex, ImVec2(imageSize, imageSize));
		static float currSpriteRect[4] = {0.25, 0.25, 0.5, 0.5};

		// Settings on the Right or Below
		{
			ImGui::SameLine();
			ImGui::BeginChild("Rect Tools", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::Text("Sprite Rect: x, y, width, height.");
			{
				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 15);
				ImGui::SliderFloat4("##RectSliders", currSpriteRect, 0.0f, 1.0f);
				ImGui::InputFloat4("##RectInputs", currSpriteRect, 4);
				ImGui::PopItemWidth();
			}
			ImGui::NewLine();
			static float spriteColor[4] = { 1, 1, 1, 1 };
			ImGui::ColorEdit4("Color", spriteColor);
			const float previewWidth = ImGui::GetItemRectSize().x;
			ImVec2 size = ImVec2(previewWidth, previewWidth * currSpriteRect[3] / currSpriteRect[2]);
			ImVec2 uvA = ImVec2(currSpriteRect[0], currSpriteRect[1]);
			ImVec2 uvB = ImVec2(uvA.x + currSpriteRect[2], uvA.y + currSpriteRect[3]);
			ImGui::Image((void *)tex, size, uvA, uvB, ImVec4(spriteColor[0], spriteColor[1], spriteColor[2], spriteColor[3]));
			ImGui::EndChild();
		}


		ImVec2 rectStartPos = ImVec2(imageStart.x + currSpriteRect[0] * imageSize, imageStart.y + currSpriteRect[1] * imageSize);
		ImVec2 rectEndPos = ImVec2(rectStartPos.x + currSpriteRect[2] * imageSize, rectStartPos.y + currSpriteRect[3] * imageSize);
		auto * drawList = ImGui::GetWindowDrawList();
		{
			ImGui::PushClipRect(imageStart, ImVec2(imageStart.x + imageSize, imageStart.y + imageSize), true);
			drawList->AddRectFilled(rectStartPos, rectEndPos, ImColor(0.3f, 1.0f, 0.3f, 0.3f));
			drawList->AddRect(rectStartPos, rectEndPos, ImColor(0.2f, 1.0f, 0.2f, 1.0f));
			ImGui::PopClipRect();
		}
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
