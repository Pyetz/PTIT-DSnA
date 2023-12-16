﻿#include "Declaration/my_fProt.h"

std::string aircraftFile = "./Media/aircraft.txt";

void string_uppercase(std::string &);
bool check_valid_planeID(std::string &);
void string_uppercase(std::string &str)
{
	for (int i = 0; i < 2; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
}

int string_length(std::string &str)
{
	int length = 0;
	while (str[length] != '\0')
		length++;
	return length;
}

bool is_planeList_empty(PlaneList &planeList)
{
	return planeList.totalPlane == 0;
}

bool is_planeList_full(PlaneList &planeList)
{
	return planeList.totalPlane == MAXPLANE;
}

void display_error(std::string error)
{
	std::cout << std::endl
			  << error << std::endl;
}

bool insert_plane(PlaneList &planeList, int &current_airline_index, char aircraft_registration_buf[], const char *&current_aircraftType, int &total_seats, int &total_rows)
{
	if (is_planeList_full(planeList))
	{
		std::cout << "The list is full";
		return 0;
	}

	planeList.nodes[planeList.totalPlane] = new Plane;
	Plane *plane = planeList.nodes[planeList.totalPlane];

	std::string aircraftRegistration;
	switch (current_airline_index)
	{
	case 0:
	case 1:
	case 2:
		aircraftRegistration = "VN-";
		break;
	case 3:
		aircraftRegistration = "A6-";
		break;
	case 4:
		aircraftRegistration = "B-";
		break;
	}

	plane->planeID = aircraftRegistration + aircraft_registration_buf;
	plane->planeType = current_aircraftType;
	plane->seatNum = total_seats;
	plane->rowNum = total_rows;

	std::cout << "created successfully!" << std::endl;

	planeList.totalPlane++;

	return 1;
}

void edit_plane(PlaneList &planeList, int &current_airline_index, char aircraft_registration_buf[], const char *&current_aircraftType, int &total_seats, int &total_rows, int &planeIndex)
{
	Plane *plane = planeList.nodes[planeIndex];

	std::string aircraftRegistration;
	switch (current_airline_index)
	{
	case 0:
	case 1:
	case 2:
		aircraftRegistration = "VN-";
		break;
	case 3:
		aircraftRegistration = "A6-";
		break;
	case 4:
		aircraftRegistration = "B-";
		break;
	}

	plane->planeID = aircraftRegistration + aircraft_registration_buf;
	plane->planeType = current_aircraftType;
	plane->seatNum = total_seats;
	plane->rowNum = total_rows;

	std::cout << "edited successfully!" << std::endl;
}

void display_planeList(PlaneList &planeList)
{
	if (is_planeList_empty(planeList))
	{
		std::cout << "The list is empty";
		return;
	}

	std::cout << "Plane ID\tPlane Type\tSeat Number\tRow Number" << std::endl;
	for (int i = 0; i < planeList.totalPlane; i++)
	{
		Plane *plane = planeList.nodes[i];
		std::cout << plane->planeID << "\t" << plane->planeType << "\t" << plane->seatNum << "\t" << plane->rowNum << std::endl;
	}
}

// void save_aircraft(PlaneList &planeList, std::string filename) //binary file
// {
// 	std::ofstream f(filename, std::ios::binary);
// 	if (f.is_open())
// 		for (int i = 0; i < planeList.totalPlane; i++)
// 		{
// 			f.write((char *)&planeList.nodes[i], sizeof(Plane));
// 		}
// 	else
// 	{
// 		std::cout << "An error occurred while opening file" << std::endl;
// 		return;
// 	}
// 	f.close();
// 	std::cout << "Saved to aircraft file successfully!" << std::endl;
// }

void save_aircraft(PlaneList &planeList, std::string &filename) // txt file
{
	std::ofstream f(filename);

	if (f.is_open())
		for (int i = 0; i < planeList.totalPlane; i++)
		{
			f << planeList.nodes[i]->planeID << '\n'
			  << planeList.nodes[i]->planeType << '\n'
			  << planeList.nodes[i]->seatNum << '\n'
			  << planeList.nodes[i]->rowNum << '\n';
		}
	else
	{
		std::cout << "An error occurred while opening file" << std::endl;
		return;
	}

	f.close();
	std::cout << "Saved to aircraft file successfully!" << std::endl;
}

// void load_aircraft(PlaneList &planeList, std::string filename) //binary file
// {
// 	std::ifstream f;
// 	f.open(filename, std::ios::binary);
// 	Plane plane;
// 	if (f.is_open())
// 		while (f.read((char *)&plane, sizeof(Plane)))
// 		{
// 			planeList.nodes[planeList.totalPlane] = new Plane;
// 			*planeList.nodes[planeList.totalPlane] = plane;
// 			planeList.totalPlane++;
// 		}
// 	else
// 	{
// 		std::cout << "An error occurred while opening file" << std::endl;
// 		return;
// 	}
// 	f.close();
// 	std::cout << "Loaded from aircraft file successfully!" << std::endl;
// }

void load_aircraft(PlaneList &planeList, std::string filename) // txt file
{
	std::ifstream f;
	f.open(filename);
	Plane plane;

	if (f.is_open())
		while (std::getline(f, plane.planeID) &&
			   std::getline(f, plane.planeType) &&
			   (f >> plane.seatNum) && f.ignore() &&
			   (f >> plane.rowNum) && f.ignore())
		{
			planeList.nodes[planeList.totalPlane] = new Plane;
			*planeList.nodes[planeList.totalPlane] = plane;
			planeList.totalPlane++;
		}
	else
	{
		std::cout << "An error occurred while opening file" << std::endl;
		return;
	}

	f.close();
	std::cout << "Loaded from aircraft file successfully!" << std::endl;
}

void delete_plane(PlaneList &planeList, int &planeIndex)
{
	// if (planeIndex < 0 || planeIndex >= planeList.totalPlane || is_planeList_empty(planeList))
	// 	return;
	for (int i = planeIndex; i < planeList.totalPlane - 1; i++)
		planeList.nodes[i] = planeList.nodes[i + 1];
	planeList.totalPlane--;
}