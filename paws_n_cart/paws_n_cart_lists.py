""" Shopping Cart String Challenge 

    Welcome to Paws n Cart, the list challenge shopping cart program.

    Unlike the string challenge which was started first,
    this time I will focus on the list object type.

"""
from random import randint
INTRO_ART = """
'||''|.                                                  ..|'''.|                   .   
 ||   ||  ....   ... ... ...  ....       .. ...        .|'     '   ....   ... ..  .||.  
 ||...|' '' .||   ||  ||  |  ||. '        ||  ||       ||         '' .||   ||' ''  ||   
 ||      .|' ||    ||| |||   . '|..       ||  ||       '|.      . .|' ||   ||      ||   
.||.     '|..'|'    |   |    |'..|'      .||. ||.       ''|....'  '|..'|' .||.     '|.' 

"""

# ITEM_SEPARATOR = '~'
# INFO_SEPARATOR = "*"
DIVIDER = "." * 50 + "\n"

def add_item(shopping_cart, price_catalog):
    """Add an item to the shopping cart and update price catalog as needed.

    Args:
        shopping_cart (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.

    Returns:
        list, list: returns the new shopping cart and price catalog
    """
    # Get user inputs for item and amount
    item = get_input("What would you like to add to your cart? ")
    if item in shopping_cart:
        print("This item is in your cart already.")
        return change_quantity(shopping_cart, price_catalog, item=item)
    amount = int(get_input(
        f"How many {item} would you like to add to your cart? ",
        valid_type=int,
    ))
    # Add new items to the price catalog.
    if item not in price_catalog:
        price = randint(20,120)
        price_catalog.extend([item, price])
    # Add the item to the cart
    for _ in range(amount):
        shopping_cart.append(item)
    return shopping_cart, price_catalog


def remove_item(shopping_cart, price_catalog, item=None):
    """Remove the full quantity of an item from the shopping cart.

    Args:
        shopping_cart (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.
        item (str): for when this is called because the input from
                    change_quantity was already in the cart. instead of
                    asking for a new item, the function will 
                    use the item given there.

    Returns:
        list, list: returns the new shopping cart and price catalog
    """
    if item is None:
        item = get_input(
            "which item would you like to remove?",
            options=shopping_cart
        )
    shopping_cart = [
        shopping
        for shopping in shopping_cart
        if shopping != item
    ]
    return shopping_cart, price_catalog


def change_quantity(shopping_cart, price_catalog, item=None):
    """Change the amount of an item in the shopping cart

    Args:
        shopping_cart (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.
        item (str): for when this is called because the input from add_item was
                    already in the cart. instead of asking for a new item, the 
                    function will use the item given there.

    Returns:
        list, list: returns the new shopping cart and price catalog
    """
    # Return if the shopping cart is empty.
    if not shopping_cart:
        print("\nYour cart is empty, please add an item first.\n")
        return shopping_cart, price_catalog
    # Get an item input if this is not given in the arguments.
    if not item:
        # Show the available items in cart and ask for relevant inputs
        print("Your cart \n", DIVIDER, "\n".join(set(shopping_cart)))
        item = get_input(
            "Which item would you like to modify the quantity of? ",
            options=shopping_cart,
        )
    selected_quantity = int(get_input(
        f"How many {item} would you like to have in your cart? ",
        valid_type=int,
    ))
    # Remove the item and then re-add the new amount
    shopping_cart, price_catalog = remove_item(
        shopping_cart,
        price_catalog,
        item=item
    )
    for _ in range(selected_quantity):
        shopping_cart.append(item)
    return shopping_cart, price_catalog


def display_cart(shopping_cart, price_catalog):
    """Display a formatted cart to the user.

    Args:
        shopping_cart (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.

    Returns:
        list, list: returns the shopping cart and price catalog
    """
    list_of_items = set(shopping_cart)
    # Calculate total price while outputting the shopping cart
    total_cost = 0
    # Categories first
    print("Name\t\t\tAmount\t\tPrice")
    for item in list_of_items:
        quantity = shopping_cart.count(item)
        price = price_catalog[price_catalog.index(item) + 1]
        print(f"{item}\t\t{quantity}\t\t{price}")
        total_cost += price * quantity
    # Output the total cost
    print(f"\nTotal:\t{total_cost}\n")

    return shopping_cart, price_catalog


def empty_cart(_, price_catalog):
    """Reset the cart to an empty list.

    Args:
        _ (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.

    Returns:
        list, list: returns the shopping cart and price catalog
    """
    return [], price_catalog



def end_program(shopping_cart, price_catalog):
    """Display a nice message and end the program.

    Args:
        shopping_cart (list): list of items in the users cart.
        price_catalog (list): list of [item, price] pairs.

    Returns:
        None: this will end the program
    """
    total = sum([
        price_catalog[price_catalog.index(item) + 1]
        for item in shopping_cart
    ])
    print(
        "Thank you for shopping with us!\n",
        f"Your total has come out to {total}.\n",
    )
    return None, None  # to end the loop


def get_input(prompt, options=None, valid_type=None, not_in=None):
    """Get a user input matching one of the options given to validate the input.

    Args:
        prompt (str): Prompt the user for an input
        options (str): List of valid options for user input. 
        valid_type (object): Check if input can be type converted to this type. 
        not_in (str): Either a list which the input should not be in
            or a string which the input should not be a substring in. 

    Returns:
        str: The valid user input
    """
    user_input = input(prompt).lower().strip()
    if options and user_input not in options:
        # Ask again when the answer is not valid.
        print(f"{user_input} is not a valid input.\n")
        return get_input(prompt, options, valid_type, not_in)
    if valid_type:
        try:
            valid_type(user_input)
        except ValueError:
            print(f"{user_input} is not a valid input.\n")
            return get_input(prompt, options, valid_type, not_in)
    if not_in and user_input in not_in:
        print(f"{user_input} is not a valid input.\n")
        return get_input(prompt, options, valid_type, not_in)
    return user_input


def main():
    """The main function controls the flow of the program.
    Welcome to Paws n Cart, the string challenge shopping cart program.

    Since this is a string challenge, this program will be
    avoiding lists and classes as much as possible.
    """
    print(INTRO_ART)
    shopping_cart = []
    price_catalog = []

    while shopping_cart is not None:
        function = menu()
        shopping_cart.sort()
        shopping_cart, price_catalog = function(shopping_cart, price_catalog)


def menu():
    """_summary_

    Returns:
        _type_: _description_
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
        options=["1", "2", "3", "4", "5", "6"]
    )
    print(DIVIDER)
    # Return the corresponding function for the menu item
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
