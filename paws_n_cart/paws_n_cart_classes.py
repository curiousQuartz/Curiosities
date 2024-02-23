"""Main class and shell interface for the shopping cart program.
"""
# Built in Modules
import random
import sys
# 3rd Party Modules
import tabulate


INTRO_ART = """
'||''|.                                                  ..|'''.|                   .   
 ||   ||  ....   ... ... ...  ....       .. ...        .|'     '   ....   ... ..  .||.  
 ||...|' '' .||   ||  ||  |  ||. '        ||  ||       ||         '' .||   ||' ''  ||   
 ||      .|' ||    ||| |||   . '|..       ||  ||       '|.      . .|' ||   ||      ||   
.||.     '|..'|'    |   |    |'..|'      .||. ||.       ''|....'  '|..'|' .||.     '|.' 

"""
DIVIDER = "." * 50 + "\n"


class ShoppingCart:
    """Shopping Cart API
    """
    def __init__(self):
        """Initialization function
        """
        self.__price_catalog = {}
        self.__cart = {}

    def __repr__(self):
        """Displays when the class is printed

        Returns:
            str: ShoppingCart([(item, quantity, price)])
        """
        catalog = []
        for item, price in self.price_catalog.items():
            catalog.append(
                (item, self.__cart.get(item, 0), price)
            )
        return f'{type(self).__name__}({catalog})'

    def add_item(self, item, quantity, price=None):
        """Add or modify the quantity of an item in the cart.
        Prices are randomly generated between ￡1.50 and ￡4.50

        Args:
            item (str): Name of the item
            quantity (int): Number of item to include in the cart
            price (float): Price for an item not yet in the price catalog.
        """
        item = item.capitalize()
        # Add new items to the price catalog.
        if item not in self.price_catalog:
            if not isinstance(price, float):
                price = random.randint(150, 450) / 100
            self.__price_catalog[item] = price
        # Add the item to the cart
        if quantity > 0:
            self.__cart[item] = quantity
        elif item in self.__cart:
            self.remove(item)

    def clear(self):
        """Clears the shopping cart of all items. 
        """
        self.__cart = {}

    @property
    def is_empty(self):
        """Property to provide a True or False value
        dependent on the state of the cart.

        Returns:
            bool: True is returned when there are no items in the cart.
        """
        return not self.__cart

    def item_info(self, item):
        """Get the relevant info for an item

        Args:
            item (str): Name of the item to search

        Returns:
            tuple(int, float): quantity in the cart followed by the price
        """
        quantity = price = 0
        if item in self.__cart:
            quantity = self.__cart[item]
        if item in self.price_catalog:
            price = self.price_catalog[item]
        return quantity, price

    def items_list(self, upper=False, lower=False):
        """Get a list of items current in the cart.

        Args:
            upper (bool): sets all names to uppercase. Defaults to False.
            lower (bool): sets all names to lowercase. Defaults to False.

        Returns:
            list(str): List of all item names which are present in the cart
        """
        if upper:
            return [item.upper() for item in self.__cart]
        if lower:
            return [item.lower() for item in self.__cart]
        return list(self.__cart)

    @property
    def price_catalog(self):
        """Price catalog property to act as a getter function.

        Returns:
            dict: Dictionary of item, price pairs.
        """
        return self.__price_catalog

    def remove(self, item):
        """Remove the given item from the cart.

        Args:
            item (str): Item name

        Returns:
            int: quantity removed from the cart
        """
        if item in self.__cart:
            self.__cart.pop(item)

    @property
    def total_cost(self):
        """Property holding the total cost of items in the cart

        Returns:
            float: total cost
        """
        return sum((
            quantity * self.price_catalog[item]
            for item, quantity in self.__cart.items()
        ))

    @property
    def total_quantity(self):
        """Property holding the total quantity of items in the cart

        Returns:
            int: total quantity
        """
        return sum((value for _, value in self.__cart.items()))


class ShellInterface:
    """Shell Interface handling for the shopping cart program.
    """
    def __init__(self):
        """Initialization function 
        launching the shell interface shopping cart program.
        """
        self.cart = ShoppingCart()

        print(INTRO_ART)

        while True:
            self.menu()
            # Program is exited by running the end_program method.

    def menu(self):
        """Displays the menu and asks the user for next action.
        """
        # Display the menu
        print(
            "What would you like to do?\n",
            DIVIDER,
            "1. Add an item to your cart.\n",
            "2. Remove an item from your cart.\n",
            "3. View the total cost of your cart.\n",
            "4. Change an item quantity.\n",
            "5. Empty your shopping cart.\n",
            "6. Checkout.\n",
        )
        # Recieve an input of which menu item they want to select
        # Must be a number on the menu
        choice = get_input(
            "Please select a number from the menu above: ",
            options=["1", "2", "3", "4", "5", "6"],
        )
        print(DIVIDER)
        # Call the corresponding function for the menu item
        if choice == "1":
            self.add_item()
        elif choice == "2":
            self.remove_item()
        elif choice == "3":
            self.display_cart()
        elif choice == "4":
            self.change_quantity()
        elif choice == "5":
            self.cart.clear()
        elif choice == "6":
            self.end_program()

    def add_item(self):
        """Add an item to the shopping cart
        """
        # Get user inputs for item and amount
        item = get_input("What would you like to add to your cart? ")
        if item.lower() in self.cart.items_list(lower=True):
            print("This item is in your cart already.")
            self.change_quantity(item=item)
        else:
            quantity = int(get_input(
                f"How many {item} would you like to add to your cart? ",
                valid_type=int,
            ))
            self.cart.add_item(item, quantity)

    def change_quantity(self, item=None):
        """Change the quantity of an item in the cart

        Args:
            item (str, optional): item name. Defaults to None.
        """
        # Return if the shopping cart is empty.
        if self.cart.is_empty:
            print("\nYour cart is empty, please add an item first.\n")
            return
        # Get an item input if this is not given in the arguments.
        if item is None:
            # Show the available items in cart and ask for relevant inputs
            self.display_items()
            item = get_input(
                "Which item would you like to modify the quantity of? ",
                options=self.cart.items_list(lower=True),
            ).capitalize()

        quantity = int(get_input(
            f"How many {item} would you like to have in your cart? ",
            valid_type=int,
        ))
        if quantity > 0:
            self.cart.add_item(item, quantity)
        else:
            self.cart.remove(item)

    def display_items(self):
        """Display only item names from the cart.
        """
        print(
            "Your cart \n", 
            DIVIDER,
            "\n ".join(self.cart.items_list()),
            "\n",
            DIVIDER,
        )

    def display_cart(self):
        """Display the cart and item information along with totals.
        """
        cart_table = []
        for item in self.cart.items_list():
            quantity, price = self.cart.item_info(item)
            cart_table.append([item, quantity, format_price(price)])
        cart_table.append([])
        cart_table.append([
            "Total",
            self.cart.total_quantity,
            format_price(self.cart.total_cost),
        ])
        # Output the total cost
        print(tabulate.tabulate(
            cart_table,
            headers=("Name", "Amount", "Price"),
        ))

    def end_program(self):
        """Ends the program with a goodbye message.
        """
        total = format_price(self.cart.total_cost)
        print(
            "Thank you for shopping with us!\n",
            f"Your total has come out to {total}.\n",
        )
        sys.exit("End of program.")

    def remove_item(self, item=None):
        """Remove an item from the cart

        Args:
            item (str, optional): Item name. Defaults to None.
        """
        if item is None:
            self.display_items()
            item = get_input(
                "which item would you like to remove? ",
                options=self.cart.items_list(lower=True)
            )
        self.cart.remove(item.capitalize())


def format_price(price):
    """Properly format price strings

    Args:
        price (float): Price float

    Returns:
        str: String formatted with 2 decimal places and a pound symbol.
    """
    return '￡%.2f' % price


def get_input(prompt, options=None, valid_type=None):
    """Get a user input matching the filters given to validate the input.

    Args:
        prompt (str): Prompt the user for an input
        options (list): Filter: List of valid options for user input. 
        valid_type (object): Filter: Check if input can be type converted to this type. 

    Returns:
        str: The valid user input
    """
    user_input = input(prompt).lower().strip()
    if options and user_input not in options:
        # Ask again when the answer is not valid.
        print(f"{user_input} is not a valid input.\n")
        return get_input(prompt, options, valid_type)
    if valid_type:
        try:
            valid_type(user_input)
        except ValueError:
            print(f"{user_input} is not a valid input.\n")
            return get_input(prompt, options, valid_type)
    return user_input

if __name__ == "__main__":
    ShellInterface()
