#include <iostream>
#include <assert.h>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <strsafe.h>

#define FILE_NAME "green_garden.bin"
#define GREEN 2
#define RED 4
#define YELLOW 6
#define WHITE 7

enum ARROWKEYS {
	KEY_UP = 72, KEY_DOWN = 80
};

enum MAINMENU {
	PRINT = 1, RATING_OPTIONS, MENU_OPTIONS, SAVE_CHANGES, EXIT
};

enum RATINGMENU
{
	INCREASE_MENU_RATING = 1, DECREASE_MENU_RATING, BACK
};

enum MENUOPTIONS
{
	ADD_MENU = 1, UPD_MENU, DEL_MENU, BACK2
};

class Menu
{
	size_t id;
	char* name;
	double menu_rating;
	char* category;
	double price;
	double tax;

public:
	static size_t current_id;

	Menu() :id(0), name(nullptr), menu_rating(0), category(nullptr), price(0), tax(0) {}

	Menu(const char* name, double menu_rating, const char* category, double price, double tax)
		:Menu(name, menu_rating, category, price)
	{
		setTax(tax);
	}

	Menu(const char* name, double menu_rating, const char* category, double price)
		:Menu(name, menu_rating, category)
	{
		setPrice(price);
	}

	Menu(const char* name, double menu_rating, const char* category)
		:Menu(name, menu_rating)
	{
		setCategory(category);
	}

	Menu(const char* name, double menu_rating)
		:Menu(name)
	{
		setMenuRating(menu_rating);
	}

	explicit Menu(const char* name)
	{
		setName(name);
		setID(++current_id);
	}

	Menu(const Menu& menu)
	{
		//std::cout << "Copy constructor" << std::endl;
		setID(menu.getID());
		setName(menu.getName());
		setMenuRating(menu.getMenuRating());
		setCategory(menu.getCategory());
		setPrice(menu.getPrice());
		setTax(menu.getTax());
	}

	Menu& operator = (const Menu& menu)
	{
		//std::cout << "Copy assignment" << std::endl;
		if (this != &menu)
		{
			delete[] this->name;
			delete[] this->category;

			setID(menu.getID());
			setName(menu.getName());
			setMenuRating(menu.getMenuRating());
			setCategory(menu.getCategory());
			setPrice(menu.getPrice());
			setTax(menu.getTax());
		}
		return *this;
	}

	Menu(Menu&& menu) noexcept
	{
		//std::cout << "Move constructor" << std::endl;
		this->id = menu.id;
		menu.id = 0;
		this->name = menu.name;
		menu.name = nullptr;
		this->menu_rating = menu.menu_rating;
		menu.menu_rating = 0;
		this->category = menu.category;
		menu.category = nullptr;
		this->price = menu.price;
		menu.price = 0;
		this->tax = menu.tax;
		menu.tax = 0;
	}

	Menu& operator = (Menu&& menu) noexcept
	{
		//std::cout << "Move assignment" << std::endl;
		if (this != &menu)
		{
			delete[] this->name;
			delete[] this->category;

			//-----------
			this->id = menu.id;
			menu.id = 0;
			this->name = menu.name;
			menu.name = nullptr;
			this->menu_rating = menu.menu_rating;
			menu.menu_rating = 0;
			this->category = menu.category;
			menu.category = nullptr;
			this->price = menu.price;
			menu.price = 0;
			this->tax = menu.tax;
			menu.tax = 0;
		}
		return *this;
	}

	void setID(size_t id)
	{
		this->id = id;
	}

	size_t getID() const
	{
		return id;
	}

	void setName(const char* name)
	{
		assert(name && "Please enter the name!");
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name, length, name);
	}

	const char* getName() const
	{
		return name;
	}

	void setMenuRating(double menu_rating)
	{
		assert(menu_rating >= 0 && menu_rating <= 10 && "Menu rating must be between 0 and 10");
		this->menu_rating = menu_rating;
	}

	double getMenuRating() const
	{
		return menu_rating;
	}

	void setCategory(const char* category)
	{
		assert(category && "Please enter the category!");
		size_t length = strlen(category) + 1;
		this->category = new char[length];
		strcpy_s(this->category, length, category);
	}

	const char* getCategory() const
	{
		return category;
	}

	void setPrice(double price)
	{
		assert(price > 0 && "Price must be greater than zero");
		this->price = price;
	}

	double getPrice() const
	{
		return price;
	}

	void setTax(double tax)
	{
		assert(tax >= 0 && "Tax must be positive number!");
		this->tax = tax;
	}

	double getTax() const
	{
		return tax;
	}

	void print() const
	{
		const char* name = getName();
		const char* category = getCategory();
		double menu_rating = getMenuRating();

		std::cout << "------------------------------------------" << std::endl;

		if (menu_rating < 4)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		else if (menu_rating < 7)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

		std::cout << "Menu id: " << getID() << std::endl;

		std::cout << "Name: ";

		if (name)
			std::cout << name << std::endl;
		else
			std::cout << "none" << std::endl;

		std::cout << "Rating: " << std::setprecision(3) << menu_rating << std::endl;

		std::cout << "Category: ";

		if (category)
			std::cout << category << std::endl;
		else
			std::cout << "none" << std::endl;

		std::cout << "Price: " << std::setprecision(3) << getPrice() << " $" << std::endl;
		std::cout << "Tax: " << getTax() << " %" << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}

	void input()
	{
		if (this->id == 0)
		{
			setID(++current_id);
		}
		else
		{
			delete[] name;
			delete[] category;
		}

		char* buff = new char[255];
		double temp = 0;
		std::cout << "Enter menu name: ";

		std::cin.ignore();
		std::cin.getline(buff, 255);

		setName(buff);

		std::cout << "Enter menu rating: ";

		std::cin >> temp;

		setMenuRating(temp);

		std::cout << "Enter menu category: ";

		std::cin.ignore();
		std::cin.getline(buff, 255);

		setCategory(buff);

		std::cout << "Enter menu price: $ ";

		std::cin >> temp;

		setPrice(temp);

		std::cout << "Enter menu tax: % ";

		std::cin >> temp;

		setTax(temp);

		delete[] buff;

		//assert(false && "Menu already created!");
	}

	Menu& operator++(int)
	{
		this->menu_rating++;

		return *this;
	}

	Menu& operator--(int)
	{
		this->menu_rating--;

		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const Menu& menu);
	friend std::istream& operator >> (std::istream& in, Menu& menu);

	~Menu()
	{
		//std::cout << "Menu destroyed!" << std::endl;
		delete[] name;
		delete[] category;
	}
};

size_t Menu::current_id = 0;

std::ostream& operator <<(std::ostream& out, const Menu& menu)
{
	menu.print();
	return out;
}

std::istream& operator >> (std::istream& in, Menu& menu)
{
	menu.input();
	return in;
}

class Restaurant
{
	static size_t no;
	char* name;
	char* address;
	char* phone_number;
	double rating;
	double average_cost;
	size_t max_menu_count;
	Menu** menu;

private:
	void setRating(double rating)
	{
		this->rating = rating;
	}
	void setAverageCost(double average_cost)
	{
		this->average_cost = average_cost;
	}

public:

	bool changes = false;

	friend std::ostream& operator <<(std::ostream& out, const Restaurant& res);
	friend std::istream& operator >>(std::istream& in, Restaurant& res);

	Restaurant() : name(nullptr), address(nullptr), phone_number(nullptr), rating(0), average_cost(0), max_menu_count(0), menu(nullptr) {}

	Restaurant(const char* name, const char* address, const char* phone_number, size_t max_menu_count, Menu** menu)
		:Restaurant(name, address, phone_number, max_menu_count)
	{
		setMenu(menu);
	}

	Restaurant(const char* name, const char* address, const char* phone_number, size_t max_menu_count)
		:Restaurant(name, address, phone_number)
	{
		setMaxMenuCount(max_menu_count);
	}

	Restaurant(const char* name, const char* address, const char* phone_number)
		:Restaurant(name, address)
	{
		setPhoneNumber(phone_number);
	}

	Restaurant(const char* name, const char* address)
		:Restaurant(name)
	{
		setAddress(address);
	}

	explicit Restaurant(const char* name)
	{
		setName(name);
	}

	Restaurant(const Restaurant& res)
	{
		//std::cout << "Copy constructor" << std::endl;
		setName(res.getName());
		setAddress(res.getAddress());
		setPhoneNumber(res.getPhoneNumber());
		setRating(res.getRating());
		setAverageCost(res.getAverageCost());
		setMaxMenuCount(res.getMaxMenuCount());
		setMenu(res.getMenu());
	}

	Restaurant& operator = (const Restaurant& res)
	{
		//std::cout << "Copy assigment!" << std::endl;

		if (this != &res)
		{
			delete[] res.name;
			delete[] res.address;
			delete[] res.phone_number;
			for (size_t i = 0; i < max_menu_count; i++)
			{
				delete menu[i];
			}
			delete[] menu;

			//----------------------------------

			setName(res.getName());
			setAddress(res.getAddress());
			setPhoneNumber(res.getPhoneNumber());
			setRating(res.getRating());
			setAverageCost(res.getAverageCost());
			setMaxMenuCount(res.getMaxMenuCount());
			setMenu(res.getMenu());
		}

		return *this;
	}

	Restaurant(Restaurant&& res) noexcept
	{
		//std::cout << "Move constructor" << std::endl;
		this->name = res.name;
		res.name = nullptr;
		this->address = res.address;
		res.address = nullptr;
		this->phone_number = res.phone_number;
		res.phone_number = nullptr;
		setRating(res.getRating());
		res.rating = 0;
		setAverageCost(res.getAverageCost());
		res.average_cost = 0;
		setMaxMenuCount(res.getMaxMenuCount());
		res.max_menu_count = 0;
		this->menu = res.menu;
		res.menu = nullptr;
	}

	Restaurant& operator=(Restaurant&& res) noexcept
	{
		//std::cout << "Move assigment!" << std::endl;

		if (this != &res)
		{
			delete[] this->name;
			delete[] this->address;
			delete[] this->phone_number;
			for (size_t i = 0; i < max_menu_count; i++)
			{
				delete menu[i];
			}
			delete[] menu;

			//-------------------------------

			this->name = res.name;
			res.name = nullptr;
			this->address = res.address;
			res.address = nullptr;
			this->phone_number = res.phone_number;
			res.phone_number = nullptr;
			setRating(res.getRating());
			res.rating = 0;
			setAverageCost(res.getAverageCost());
			res.average_cost = 0;
			setMaxMenuCount(res.getMaxMenuCount());
			res.max_menu_count = 0;
			this->menu = res.menu;
			res.menu = nullptr;
		}

		return *this;
	}

	void setName(const char* name)
	{
		assert(name && "Enter the restaurant name");
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name, length, name);
	}

	const char* getName() const
	{
		return name;
	}

	void setAddress(const char* address)
	{
		assert(address && "Enter the restaurant name");
		size_t length = strlen(address) + 1;
		this->address = new char[length];
		strcpy_s(this->address, length, address);
	}

	const char* getAddress() const
	{
		return address;
	}

	void setPhoneNumber(const char* phone_number)
	{
		assert(phone_number && "Enter the phone number");
		size_t length = strlen(phone_number) + 1;
		this->phone_number = new char[length];
		strcpy_s(this->phone_number, length, phone_number);
	}

	const char* getPhoneNumber() const
	{
		return phone_number;
	}

	static size_t getRestaurantNo()
	{
		return no;
	}

	double getRating() const
	{
		return rating;
	}

	double getAverageCost() const
	{
		return average_cost;
	}

	void setMaxMenuCount(size_t max_menu_count)
	{
		assert(max_menu_count > 0 && "Max menu count must be greater than zero");
		this->max_menu_count = max_menu_count;
	}

	size_t getMaxMenuCount() const
	{
		return max_menu_count;
	}

	void setMenu(Menu** menu)
	{
		assert(menu && "Null error!");

		this->menu = new Menu * [this->max_menu_count];

		if (this->menu)
		{
			for (size_t i = 0; i < this->max_menu_count; i++)
			{
				this->menu[i] = new Menu(*menu[i]);
			}

			sortMenu(true);
			calcAverageCost();
			calcAverageRating();
		}
	}

	void print() const
	{
		const char* name = getName();
		const char* address = getAddress();
		const char* phone_number = getPhoneNumber();
		size_t menu_count = getMaxMenuCount();
		double rating = getRating();
		std::cout << "Restaurant no: " << no << std::endl;
		std::cout << "Name: ";

		if (name)
			std::cout << name << std::endl;
		else
			std::cout << "none" << std::endl;

		std::cout << "Address: ";

		if (address)
			std::cout << address << std::endl;
		else
			std::cout << "none" << std::endl;

		std::cout << "Phone number: ";

		if (phone_number)
			std::cout << phone_number << std::endl;
		else
			std::cout << "none" << std::endl;

		std::cout << "Rating: ";

		if (rating < 4)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		else if (rating < 7)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

		std::cout << std::setprecision(3) << getRating() << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);


		std::cout << "Average cost: " << std::setprecision(3) << getAverageCost() << " $" << std::endl;

		std::cout << "Menu count: " << max_menu_count << std::endl;
		printMenu();
	}

	void printMenu() const
	{
		if (max_menu_count)
		{
			std::cout << std::endl;
			for (size_t i = 0; i < max_menu_count; i++)
			{
				std::cout << *menu[i];
			}
		}
	}

	void input()
	{

		char* buff = new char[255];
		size_t menu_count = 0;
		std::cout << "Enter restaurant name: ";
		std::cin.getline(buff, 255);

		setName(buff);

		std::cout << "Enter restaurant address: ";

		std::cin.getline(buff, 255);

		setAddress(buff);

		std::cout << "Enter restaurant phone number: ";

		std::cin.getline(buff, 255);

		setPhoneNumber(buff);

		std::cout << "Enter menu count: ";

		std::cin >> menu_count;

		if (menu_count)
		{
			for (size_t i = 0; i < menu_count; i++)
			{
				auto new_menu = new Menu;

				std::cin >> *new_menu;

				addMenu(*new_menu);

				delete new_menu;
			}
		}
		else
			this->menu = nullptr;
	}

	Menu** getMenu() const
	{
		return menu;
	}

	void setStatusOfChanges(bool state)
	{
		this->changes = state;
	}

	bool getStatusOfChanges() const
	{
		return changes;
	}

	void calcAverageCost()
	{
		if (max_menu_count)
		{
			double average_cost = 0;

			for (size_t i = 0; i < max_menu_count; i++)
			{
				average_cost += menu[i]->getPrice();
			}

			average_cost /= max_menu_count;

			setAverageCost(average_cost);
			setStatusOfChanges(true);
		}
	}

	void calcAverageRating()
	{
		if (max_menu_count)
		{
			double average_rating = 0;

			for (size_t i = 0; i < max_menu_count; i++)
			{
				average_rating += menu[i]->getMenuRating();
			}

			average_rating /= max_menu_count;

			setRating(average_rating);
			setStatusOfChanges(true);
		}
	}

	bool addMenu(Menu& menu)
	{
		size_t new_size = getMaxMenuCount() + 1;
		auto new_menu = new Menu * [new_size];

		if (new_menu)
		{
			if (new_size - 1)
			{
				for (size_t i = 0; i < new_size - 1; i++)
				{
					new_menu[i] = new Menu;
					*new_menu[i] = std::move(*this->menu[i]);
				}
			}

			new_menu[new_size - 1] = new Menu(menu);
			this->menu = new_menu;
			setMaxMenuCount(new_size);
			sortMenu(true);
			calcAverageCost();
			calcAverageRating();
			setStatusOfChanges(true);
			return true;
		}
		return false;
	}

	bool deleteMenu(size_t id)
	{
		assert(id > 0 && "ID must be greater than zero");

		if (menu)
		{
			size_t new_size = getMaxMenuCount() - 1;

			auto new_menu = new Menu * [new_size];

			if (new_menu)
			{
				if (new_size != 0)
				{
					for (size_t i = 0, j = 0, length = new_size + 1; i < length; i++)
					{
						if (id != menu[i]->getID())
						{
							new_menu[j] = new Menu;
							*new_menu[j] = std::move(*menu[i]);
							j++;
						}
						else
						{
							delete menu[i];
							menu[i] = nullptr;
						}
					}
				}
				else
				{
					delete menu[0];
					menu[0] = nullptr;
					new_menu = nullptr;
				}

				this->max_menu_count = new_size;
				this->menu = new_menu;

				sortMenu(true);
				calcAverageCost();
				calcAverageRating();
				setStatusOfChanges(true);
				return true;
			}
		}
		else
			std::cout << "There is no menu!" << std::endl;

		return false;
	}

	bool updateMenu(size_t id)
	{
		assert(id > 0 && "ID must be greater than zero");

		if (menu)
		{
			for (size_t i = 0; i < max_menu_count; i++)
			{
				if (id == menu[i]->getID())
				{
					std::cin >> *menu[i];
					sortMenu(true);
					calcAverageCost();
					calcAverageRating();
					setStatusOfChanges(true);
					return true;
				}
			}
		}
		return false;
	}

	void increaseMenuRating(size_t id)
	{
		if (menu)
		{
			for (size_t i = 0; i < max_menu_count; i++)
			{
				if (id == menu[i]->getID())
				{
					double menu_rating = menu[i]->getMenuRating();
					if (menu_rating <= 9)
					{
						(*menu[i])++;
						sortMenu(true);
						setStatusOfChanges(true);
					}
					if (menu_rating < 10)
					{
						menu[i]->setMenuRating(10);
						sortMenu(true);
						setStatusOfChanges(true);
					}
					return;
				}
			}
		}
	}

	void decreaseMenuRating(size_t id)
	{
		if (menu)
		{
			for (size_t i = 0; i < max_menu_count; i++)
			{
				if (id == menu[i]->getID())
				{
					double menu_rating = menu[i]->getMenuRating();
					if (menu_rating >= 1)
					{
						(*menu[i])--;
						sortMenu(true);
						setStatusOfChanges(true);
					}
					else if (menu_rating > 0)
					{
						menu[i]->setMenuRating(0);
						sortMenu(true);
						setStatusOfChanges(true);
					}
					return;
				}
			}
		}
	}

	void sortMenu(bool reverse = false)
	{
		if (reverse)
		{
			for (size_t i = 0, length = getMaxMenuCount() - 1; i < length; i++)
			{
				bool swapped = false;
				for (size_t j = 0; j < length; j++)
				{
					if (menu[j]->getMenuRating() < menu[j + 1]->getMenuRating())
					{
						auto tmp = new Menu(std::move(*menu[j + 1]));
						*menu[j + 1] = std::move(*menu[j]);
						*menu[j] = std::move(*tmp);

						if (!swapped)
							swapped = true;
					}
				}

				if (!swapped)
					break;
			}
		}
		else
		{
			for (size_t i = 0, length = getMaxMenuCount() - 1; i < length; i++)
			{
				bool swapped = false;
				for (size_t j = 0; j < length; j++)
				{
					if (menu[j]->getMenuRating() > menu[j + 1]->getMenuRating())
					{
						auto tmp = new Menu(std::move(*menu[j + 1]));
						*menu[j + 1] = std::move(*menu[j]);
						*menu[j] = std::move(*tmp);

						if (!swapped)
							swapped = true;
					}
				}

				if (!swapped)
					break;
			}
		}
	}

	bool saveToFile()
	{
		FILE* file;

		fopen_s(&file, FILE_NAME, "wb");

		if (file)
		{
			fwrite(&no, sizeof(size_t), 1, file);
			size_t length = strlen(getName()) + 1;
			fwrite(&length, sizeof(size_t), 1, file);
			fwrite(getName(), sizeof(char), length, file);
			length = strlen(getAddress()) + 1;
			fwrite(&length, sizeof(size_t), 1, file);
			fwrite(getAddress(), sizeof(char), length, file);
			length = strlen(getPhoneNumber()) + 1;
			fwrite(&length, sizeof(size_t), 1, file);
			fwrite(getPhoneNumber(), sizeof(char), length, file);

			fwrite(&rating, sizeof(double), 1, file);
			fwrite(&average_cost, sizeof(double), 1, file);

			fwrite(&Menu::current_id, sizeof(size_t), 1, file);

			size_t menu_count = getMaxMenuCount();
			fwrite(&menu_count, sizeof(size_t), 1, file);

			if (menu_count)
			{
				for (size_t i = 0; i < menu_count; i++)
				{
					size_t id = menu[i]->getID();
					double temp;

					fwrite(&id, sizeof(size_t), 1, file);
					length = strlen(menu[i]->getName()) + 1;
					fwrite(&length, sizeof(size_t), 1, file);
					fwrite(menu[i]->getName(), sizeof(char), length, file);
					temp = menu[i]->getMenuRating();
					fwrite(&temp, sizeof(double), 1, file);
					length = strlen(menu[i]->getCategory()) + 1;
					fwrite(&length, sizeof(size_t), 1, file);
					fwrite(menu[i]->getCategory(), sizeof(char), length, file);
					temp = menu[i]->getPrice();
					fwrite(&temp, sizeof(double), 1, file);
					temp = menu[i]->getTax();
					fwrite(&temp, sizeof(double), 1, file);
				}

			}

			fclose(file);
			setStatusOfChanges(false);
			return true;
		}

		return false;
	}

	bool readFromFile()
	{
		FILE* file;
		fopen_s(&file, FILE_NAME, "rb");

		if (file)
		{
			size_t length = 0;
			fread(&no, sizeof(size_t), 1, file);

			fread(&length, sizeof(size_t), 1, file);

			name = new char[length];

			fread(name, sizeof(char), length, file);

			fread(&length, sizeof(size_t), 1, file);

			address = new char[length];

			fread(address, sizeof(char), length, file);

			fread(&length, sizeof(size_t), 1, file);

			phone_number = new char[length] {};

			fread(phone_number, sizeof(char), length, file);

			fread(&rating, sizeof(double), 1, file);
			fread(&average_cost, sizeof(double), 1, file);

			fread(&Menu::current_id, sizeof(size_t), 1, file);

			fread(&max_menu_count, sizeof(size_t), 1, file);

			if (max_menu_count)
			{
				this->menu = new Menu * [max_menu_count];
				for (size_t i = 0; i < max_menu_count; i++)
				{
					this->menu[i] = new Menu;
					size_t id;
					fread(&id, sizeof(size_t), 1, file);
					menu[i]->setID(id);
					fread(&length, sizeof(size_t), 1, file);
					char* buff = new char[length];

					fread(buff, sizeof(char), length, file);
					menu[i]->setName(buff);

					delete[] buff;

					double temp;
					fread(&temp, sizeof(double), 1, file);

					menu[i]->setMenuRating(temp);

					fread(&length, sizeof(size_t), 1, file);
					buff = new char[length];

					fread(buff, sizeof(char), length, file);

					menu[i]->setCategory(buff);

					fread(&temp, sizeof(double), 1, file);

					menu[i]->setPrice(temp);

					fread(&temp, sizeof(double), 1, file);

					menu[i]->setTax(temp);
				}
			}

			fclose(file);
			return true;
		}
		return false;
	}
	~Restaurant()
	{
		//std::cout << "Restaurant destroyed!" << std::endl;
		delete[] name;
		delete[] address;
		delete[] phone_number;

		for (size_t i = 0; i < max_menu_count; i++)
		{
			delete menu[i];
		}
		delete[] menu;
	}
};

size_t Restaurant::no = 145;
std::ostream& operator <<(std::ostream& out, const Restaurant& res)
{
	res.print();
	return out;
}

std::istream& operator >> (std::istream& in, Restaurant& res)
{
	res.input();
	return in;
}

struct ScreenOptions
{
	char** main_menu = nullptr;
	size_t mm_size = 0;
	char** rating_options = nullptr;
	size_t ro_size = 0;
	char** menu_options = nullptr;
	size_t mo_size = 0;
};

short MainMenu(ScreenOptions&);
short RatingOptions(ScreenOptions&);
short MenuOptions(ScreenOptions&);
void StartScreen();
void destroyData(char** options, size_t size);

void Pause()
{
	std::cout << "Press enter to continue";

	std::cin.ignore();
	std::cin.get();
}

void ConsoleScreenSettings()
{
	HANDLE hConsoleIN = GetStdHandle(STD_INPUT_HANDLE);

	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);

	TCHAR consoleNewTitle[MAX_PATH];

	StringCchPrintf(consoleNewTitle, MAX_PATH, TEXT("Restaurant: Green Garden 145"));

	SetConsoleTitle(consoleNewTitle);

	HWND consoleWindow = GetConsoleWindow();
	MoveWindow(consoleWindow, 500, 58, 895, 518, TRUE);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);


	CONSOLE_CURSOR_INFO cursor_info = {};

	cursor_info.bVisible = false;
	cursor_info.dwSize = 1;
	SetConsoleCursorInfo(hConsoleOUT, &cursor_info);
}

void main()
{
	ConsoleScreenSettings();
	StartScreen();

	ScreenOptions so;

	Restaurant res;

	if (!res.readFromFile())
	{
		Menu* m1 = new Menu("Merci", 7.3, "Shorbalar", 4.9, 15);
		Menu* m2 = new Menu("Toyuq shorbasi", 8.2, "Shorbalar", 4.9, 15);
		Menu* m3 = new Menu("Ag pendir", 6.5, "Qelyanaltilar", 4, 15);
		Menu* m4 = new Menu("Zeytun", 5.4, "Qelyanaltilar", 4.95, 15);
		Menu* m5 = new Menu("Bilinchik (et)", 8.6, "Qelyanaltilar", 2, 15);
		Menu* m6 = new Menu("Burger mal eti ile", 7.6, "Burgerler", 11.9, 15);
		Menu* m7 = new Menu("Burger toyuq eti ile", 8.6, "Burgerler", 8, 15);
		Menu* m8 = new Menu("Cola, Fanta, Sprite", 9.3, "Ichkiler", 4, 15);
		Menu* m9 = new Menu("Sirab Qazli/Qazsiz", 8.2, "Ichkiler", 4, 15);
		Menu* m10 = new Menu("Kufte bozbash", 3.2, "Milli Metbex", 6.9, 15);

		size_t max_menu_count = 10;
		Menu** menu = new Menu * [max_menu_count] {m1, m2, m3, m4, m5, m6, m7,
			m8, m9, m10};
		res.setName("Green Garden 145");
		res.setAddress("F.Bayramov St. 1130/33 Baku Azerbaijan");
		res.setPhoneNumber("+994 51 400 01 45");
		res.setMaxMenuCount(max_menu_count);
		res.setMenu(menu);

		for (size_t i = 0; i < max_menu_count; i++)
		{
			delete menu[i];
		}
	}

	while (true)
	{
		system("CLS");
		short choice = MainMenu(so);

		switch (choice)
		{
		case PRINT:
		{
			system("CLS");
			std::cout << res << std::endl;
			Pause();
		}
		break;
		case RATING_OPTIONS:
		{
			while (true)
			{
				system("CLS");
				short choice2 = RatingOptions(so);

				if (choice2 == BACK)
				{
					break;
				}

				system("CLS");
				res.printMenu();

				size_t id = 0;
				std::cout << "Enter menu id: ";
				std::cin >> id;

				switch (choice2)
				{
				case INCREASE_MENU_RATING:
				{
					res.increaseMenuRating(id);
				}
				break;
				case DECREASE_MENU_RATING:
				{
					res.decreaseMenuRating(id);
				}
				break;
				default:
					break;
				}

				system("CLS");
				res.printMenu();
				Pause();
			}
		}
		break;
		case MENU_OPTIONS:
		{
			while (true)
			{
				short choice2 = MenuOptions(so);

				system("CLS");

				if (choice2 == BACK2)
					break;
				switch (choice2)
				{
				case ADD_MENU:
				{
					auto new_menu = new Menu;

					std::cin >> *new_menu;

					res.addMenu(*new_menu);

					delete new_menu;
				}
				break;
				case UPD_MENU:
				{
					res.printMenu();
					std::cout << "Enter menu id: ";
					size_t id;

					std::cin >> id;
					res.updateMenu(id);
				}
				break;
				case DEL_MENU:
				{
					res.printMenu();
					std::cout << "Enter menu id: ";
					size_t id;

					std::cin >> id;

					res.deleteMenu(id);
				}
				break;
				default:
					break;
				}

				system("CLS");
				res.printMenu();
				Pause();
			}
		}
		break;
		case SAVE_CHANGES:
		{
			if (res.getStatusOfChanges())
				res.saveToFile();
		}
		break;
		case EXIT:
		{
			system("CLS");

			destroyData(so.main_menu, so.mm_size);
			destroyData(so.rating_options, so.ro_size);
			destroyData(so.menu_options, so.mo_size);
			return;
		}
		break;
		default:
			break;
		}

	}
}

void PrintMenu(char** options, int size, int selected);

short MenuInputWithKeyboard(char** options, short size, short& selected)
{
	while (true)
	{
		system("CLS");
		PrintMenu(options, size, selected - 1);

		int key = _getch();

		if (key == 224)
		{
			switch (_getch())
			{
			case KEY_UP:
			{
				if (selected > 1)
					selected--;
			}
			break;
			case KEY_DOWN:
			{
				if (selected < size)
					selected++;
			}
			break;
			}
		}
		else if (key == 13)
		{
			return selected;
		}
	}
}

void destroyData(char** options, size_t size)
{
	if (options)
	{
		for (size_t i = 0; i < size; i++)
		{
			delete[] options[i];
		}
		delete[] options;
		options = nullptr;
	}
}

short MainMenu(ScreenOptions& so)
{
	system("CLS");
	static short selected = 1;
	if (so.mm_size == 0)
	{
		so.mm_size = 5;
		so.main_menu = new char* [so.mm_size];
		so.main_menu[0] = _strdup("Print restaurant");
		so.main_menu[1] = _strdup("Rating options");
		so.main_menu[2] = _strdup("Menu options");
		so.main_menu[3] = _strdup("Save changes");
		so.main_menu[4] = _strdup("Exit");
	}

	return MenuInputWithKeyboard(so.main_menu, so.mm_size, selected);
}

short MenuOptions(ScreenOptions& so)
{

	system("CLS");
	static short selected = 1;
	if (so.mo_size == 0)
	{
		so.mo_size = 4;
		so.menu_options = new char* [so.mo_size];
		so.menu_options[0] = _strdup("Add Menu");
		so.menu_options[1] = _strdup("Update menu");
		so.menu_options[2] = _strdup("Delete menu");
		so.menu_options[3] = _strdup("Back");
	}

	return  MenuInputWithKeyboard(so.menu_options, so.mo_size, selected);
}

short RatingOptions(ScreenOptions& so)
{
	system("CLS");
	static short selected = 1;
	if (so.ro_size == 0)
	{
		so.ro_size = 3;
		so.rating_options = new char* [so.ro_size];
		so.rating_options[0] = _strdup("Increase Menu Rating");
		so.rating_options[1] = _strdup("Decrease Menu Rating");
		so.rating_options[2] = _strdup("Back");
	}
	return MenuInputWithKeyboard(so.rating_options, so.ro_size, selected);
}

void PrintMenu(char** options, int size, int selected)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = { 50, 10 };
	for (size_t i = 0; i < size; i++)
	{
		SetConsoleCursorPosition(hConsoleOUT, coordinate);
		if (i == selected)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			std::cout << i + 1 << ". " << options[i] << std::endl;;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else
		{
			std::cout << i + 1 << ". " << options[i] << std::endl;;
		}
		coordinate.Y++;
	}
}


void TypingEffect(const char* text)
{
	for (size_t i = 0, length = strlen(text); i < length; i++)
	{
		std::cout << text[i];

		Sleep(50);
	}
	std::cout << std::endl;
}

void StartScreen()
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOUT, { 43, 12 });
	TypingEffect("Green Garden 145");
	std::cout << std::endl;
	SetConsoleCursorPosition(hConsoleOUT, { 43, 13 });
	TypingEffect("Control panel loading...");
	Sleep(1000);
}