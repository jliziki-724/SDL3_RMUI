#ifndef WINDOW_H
#define WINDOW_H



#include "UIFCore.h"

namespace UIF{
        
	enum class FRAME_RATE{
		_30FPS = 30,
		_50FPS = 50,
		_60FPS = 60
	};

	enum class PARTITION{
		BI = 2,
		QUAD = 4,
		OCTAL = 8
	};

	struct Dimensions{
		int w{};
		int h{};
	};

	class Window{
	 private:
		SDL_Window* window{ nullptr };
    		SDL_Renderer* renderer { nullptr };
		SDL_WindowID id{};

		Dimensions win_dim{};
	        uint64_t priority{}; //Precedence based on timestamp	

		int total_partitions{ static_cast<int>(UIF::PARTITION::OCTAL) }; //Dynamic adjustment of partitions?
		int frame_rate{ static_cast<int>(UIF::FRAME_RATE::_60FPS) };
		int partition_size{};

		//Embedding Component into Window? 
		std::vector<std::vector<UIF::Component*>> partition_vec;
		std::vector<std::vector<UIF::Component*>>& Get_Partitions();

		const uint32_t CVec_ID{};
		std::string title{};

		bool is_active{ true };
		bool Is_Init() const;

		void Set_Priority(uint64_t t_stamp);
		void Set_Active(bool new_active);
		void Set_Frame_Rate(int new_frame_rate);
		void Update_Dimensions();

 		void Set_Partition_Size(int new_partition_size);
		void Set_Total_Partitions(int new_total_partitions);


		int Get_Frame_Rate();
		int Get_Partition_Size();	
		int Get_Total_Partitions();

		uint64_t Get_Priority();

		const std::string& Get_Title();

		Window(uint32_t cvec_id, std::string_view t, int w, int h, int flag);
	 public:

		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete; 

  		SDL_Window* Get_Window();
		SDL_Renderer* Get_Renderer();
		SDL_WindowID Get_ID();

		bool Is_Active();

		uint32_t Get_CVec_ID();
		const UIF::Dimensions& Get_Dimensions();

		friend WindowManager;
	};

};

#endif //WINDOW_H
