""" Shopping Cart String Challenge 

    Welcome to Paws n Cart, the string challenge shopping cart program.

    Since this is a string challenge, this program will be
    avoiding lists and classes as much as possible.
    Toward that goal, I will also avoid split() and join() where possible.
"""
import re
from random import randint


INTRO_ART = """
'||''|.                                                  ..|'''.|                   .   
 ||   ||  ....   ... ... ...  ....       .. ...        .|'     '   ....   ... ..  .||.  
 ||...|' '' .||   ||  ||  |  ||. '        ||  ||       ||         '' .||   ||' ''  ||   
 ||      .|' ||    ||| |||   . '|..       ||  ||       '|.      . .|' ||   ||      ||   
.||.     '|..'|'    |   |    |'..|'      .||. ||.       ''|....'  '|..'|' .||.     '|.' 

"""
ITEM_SEPARATOR = '~'
INFO_SEPARATOR = "*"
DIVIDER = "." * 50 + "\n"


def add_item(shopping_cart, price_catalog):
    """Add an item to the shopping cart and update price catalog as needed.

    Args:
        shopping_cart (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.

    Returns:
        str, str: returns the new shopping cart and price catalog
    """
    # Get user inputs for item and amount
    item = get_input("What would you like to add to your cart? ")
    if shopping_cart.find(ITEM_SEPARATOR + item + INFO_SEPARATOR) != -1:
        print("This item is in your cart already.")
        return change_quantity(shopping_cart, price_catalog, item=item)
    amount = get_input(
        f"How many {item} would you like to add to your cart? ",
        valid_type=int,
    )
    # Add new items to the price catalog.
    if ITEM_SEPARATOR+item+INFO_SEPARATOR not in price_catalog:
        price = randint(20,120)
        price_catalog += f"{ITEM_SEPARATOR}{item}{INFO_SEPARATOR}{price}"
    # Add the item to the cart
    shopping_cart += ITEM_SEPARATOR + item + INFO_SEPARATOR + amount
    return shopping_cart, price_catalog


def remove_item(shopping_cart, price_catalog):
    """Remove the full quantity of an item from the shopping cart.

    Args:
        shopping_cart (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.

    Returns:
        str, str: returns the new shopping cart and price catalog
    """
    item = get_input(
        "which item would you like to remove? ",
        options=get_item_list(shopping_cart, remove_info_separator=False)
    )

    index = shopping_cart.find(item)
    length = shopping_cart[index:].find(ITEM_SEPARATOR)
    if length == -1:
        # item is at the end o the list so only keep the items before it
        # the index - 1 is to exclude the separator as well
        shopping_cart = shopping_cart[:index - 1]
    elif index == 1:
        # item is at the beginning of the list so keep everything after
        shopping_cart = shopping_cart[index+length:]
    else:
        # item is in the middle so split based on the full item string
        # and reconnect the parts before and after.
        remove_section = shopping_cart[index-1:index+length]
        shopping_cart = "".join(shopping_cart.split(remove_section))
    return shopping_cart, price_catalog


def change_quantity(shopping_cart, price_catalog, item=None):
    """Change the amount of an item in the shopping cart

    Args:
        shopping_cart (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.
        item (str): for when this is called because the input from add_item was
                    already in the cart. instead of asking for a new item, the 
                    function will use the item given there.

    Returns:
        str, str: returns the new shopping cart and price catalog
    """
    # Return if the shopping cart is empty.
    if not shopping_cart:
        print("\nYour cart is empty, please add an item first.\n")
        return shopping_cart, price_catalog
    # Get an item input if this is not given in the arguments.
    if not item:
        # Show the available items in cart and ask for relevant inputs
        item_list = get_item_list(shopping_cart).replace(ITEM_SEPARATOR, "\n")
        print("Your cart \n", DIVIDER, item_list)
        item = get_input(
            "Which item would you like to modify the quantity of? ",
            options=get_item_list(shopping_cart),
        )
    selected_quantity = int(get_input(
        f"How many {item} would you like to have in your cart? ",
        valid_type=int,
    ))
    # Remove the item and then re-add the new amount
    item_index = shopping_cart.find(item)
    start_index = shopping_cart[item_index:].find(INFO_SEPARATOR) + item_index
    end_index = shopping_cart[item_index:].find(ITEM_SEPARATOR)
    cart = f"{shopping_cart[:start_index]}{INFO_SEPARATOR}{selected_quantity}"
    # End index of -1 means there are no other items in the list.
    if end_index != -1:
        cart += shopping_cart[end_index + len(ITEM_SEPARATOR):]

    return cart, price_catalog


def display_cart(shopping_cart, price_catalog):
    """Display a formatted cart to the user.

    Args:
        shopping_cart (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.

    Returns:
        list, list: returns the shopping cart and price catalog
    """
    total_cost = 0
    print("Name\t\t\tAmount\t\tPrice")
    for item in shopping_cart[1:].split(ITEM_SEPARATOR):
        if not item:
            continue
        # Separate relevant information
        name, amount = item.split(INFO_SEPARATOR)
        price = find_price(price_catalog, name)
        # Print item row and add to total price
        tabs = "\t\t"
        if len(name) < 8:
            tabs = "\t\t\t"
        print(f"{name}{tabs}{amount}\t\t{price}")
        total_cost += int(amount) * int(price)
    # Output the total cost
    print(f"\nTotal:\t{total_cost}\n")

    return shopping_cart, price_catalog


def empty_cart(_, price_catalog):
    """Reset the cart to an empty list.

    Args:
        _ (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.

    Returns:
        str, str: returns the shopping cart and price catalog
    """
    # Reset shopping cart by returning empty string instead of cart string.
    return "", price_catalog



def end_program(shopping_cart, price_catalog):
    """Display a nice message and end the program.

    Args:
        shopping_cart (str): list of items in the users cart.
        price_catalog (str): list of item/price pairs.

    Returns:
        None: this is the condition to end the program
    """
    total_cost = 0
    for item in shopping_cart[1:].split(ITEM_SEPARATOR):
        if not item:
            continue
        # Separate relevant information
        name, amount = item.split(INFO_SEPARATOR)
        price = find_price(price_catalog, name)
        # Print item row and add to total price
        total_cost += int(amount) * int(price)
    # Output the total cost and thank you message
    print(
        "Thank you for shopping with us!",
        f"\n\nYour total has come out to {total_cost}.\n",
    )
    return None, None  # to end the loop


def find_price(price_catalog, name):
    """Find the price of an item in the catalog

    Args:
        price_catalog (str): list of items and prices
        name (str): name of item

    Returns:
        str: the price of the item as a string
    """
    # Use the item and info separators to find the items' start and end index
    index = price_catalog.find(ITEM_SEPARATOR+name+INFO_SEPARATOR)
    price_start = price_catalog[index:].find(INFO_SEPARATOR) + index + 1
    price_end = price_catalog[index:].find(ITEM_SEPARATOR) + index
    # if price_end was -1 before adding index,
    # aka. no more item separators were found,
    # the item was the last one in the list.
    if price_end == index-1:
        price_end = None
    price = price_catalog[price_start:price_end]

    return price


def get_input(prompt, options=None, valid_type=None):
    """Get a user input matching one of the options given to validate the input.

    Args:
        prompt (str): Prompt the user for an input
        options (str): List of valid options for user input. 
        valid_type (object): Check if input can be type converted to this type.

    Returns:
        str: The valid user input
    """
    user_input = input(prompt).lower().strip()
    if options and options.find(ITEM_SEPARATOR + user_input) == -1:
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


def get_item_list(shopping_cart, remove_info_separator=True):
    """ Remove amount number and info separator 
        to return a list of only items and item separators.

    Args:
        shopping_cart (str): list of items and amounts in the users cart.

    Returns:
        str: list of items in the users cart.
    """
    if remove_info_separator:
        item_list = re.sub(f"[{INFO_SEPARATOR}0-9]", "", shopping_cart)
    else:
        item_list = re.sub("[0-9]", "", shopping_cart)
    return item_list


def main():
    """The main function controls the flow of the program.
    Welcome to Paws n Cart, the string challenge shopping cart program.

    Since this is a string challenge, this program will be
    avoiding lists and classes as much as possible.
    """
    print(INTRO_ART)
    shopping_cart = ""
    price_catalog = ""

    while shopping_cart is not None:
        function = menu()
        shopping_cart, price_catalog = function(shopping_cart, price_catalog)


def menu():
    """Displays the menu and asks the user for next action.
    
    Every function returned by the menu must 
    include the necessary inputs and outputs.
    ex. shopping_cart, price_catalog

    Returns:
        func: returns an executable function 
              corresponding to the menu option selected
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
        options=f"{ITEM_SEPARATOR}1{ITEM_SEPARATOR}2"\
                f"{ITEM_SEPARATOR}3{ITEM_SEPARATOR}4"\
                f"{ITEM_SEPARATOR}5{ITEM_SEPARATOR}6",
    )
    print(DIVIDER)
    # Return the corresponding function for the menu item
    # Each function must have the same required inputs and outputs.
    match choice:
        case "1":
            return add_item
        case "2":
            return remove_item
        case "3":
            return display_cart
        case "4":
            return change_quantity
        case "5":
            return empty_cart
        case "6":
            return end_program


if __name__ == "__main__":
    main()
