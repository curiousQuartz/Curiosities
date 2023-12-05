""" Shopping Cart String Challenge """
from string import capwords

INTRO_ART = """
'||''|.                                                  ..|'''.|                   .   
 ||   ||  ....   ... ... ...  ....       .. ...        .|'     '   ....   ... ..  .||.  
 ||...|' '' .||   ||  ||  |  ||. '        ||  ||       ||         '' .||   ||' ''  ||   
 ||      .|' ||    ||| |||   . '|..       ||  ||       '|.      . .|' ||   ||      ||   
.||.     '|..'|'    |   |    |'..|'      .||. ||.       ''|....'  '|..'|' .||.     '|.' 

"""

ITEM_SEPARATOR = '~'
INFO_SEPARATOR = "+"
DIVIDER = "*" * 50 + "\n"

PRICE_CATALOG = \
    f"food{INFO_SEPARATOR}10{ITEM_SEPARATOR}" \
    f"toy{INFO_SEPARATOR}30{ITEM_SEPARATOR}" \
    f"luxury{INFO_SEPARATOR}100{ITEM_SEPARATOR}" \
    f"fancy{INFO_SEPARATOR}70{ITEM_SEPARATOR}" \
    f"quality{INFO_SEPARATOR}50{ITEM_SEPARATOR}"


def add_item(shopping_cart):
    item = get_input("What would you like to add to your cart? ")
    amount = get_input(
        f"How many {item} would you like to add to your cart? ",
        valid_type=int,
    )
    price = 20
    # Add to the base price by matching words in the name to the price catalog.
    for word in item.split():
        if PRICE_CATALOG.find(word) != -1:
            index = PRICE_CATALOG.find(word)
            price_index = len(word) + len(INFO_SEPARATOR) + index
            separator_index = PRICE_CATALOG[price_index:].find(ITEM_SEPARATOR)
            price_string = PRICE_CATALOG[price_index:price_index+separator_index]
            price += int(price_string)
    
    shopping_cart += ITEM_SEPARATOR + item
    shopping_cart += INFO_SEPARATOR + amount
    shopping_cart += INFO_SEPARATOR + str(price)
    return shopping_cart


def change_quantity(shopping_cart, item=None):
    if not shopping_cart:
        print("Your cart is empty, please add an item first.")
        return shopping_cart
    if not item:
        display_cart(shopping_cart)
        selected_item = input("Which item would you like to modify the quantity of? ")
    


def display_cart(shopping_cart):
    formatted_cart = f"\nName{INFO_SEPARATOR}Amount{INFO_SEPARATOR}Price per unit"
    formatted_cart += shopping_cart.replace(ITEM_SEPARATOR, "\n- ")
    formatted_cart = formatted_cart.replace(INFO_SEPARATOR, "\t\t")
    print(f"Your Cart:{formatted_cart.title()}")
    return shopping_cart


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
    user_input = input(prompt).lower()
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
    shopping_cart=""

    while shopping_cart is not None:
        function = menu()
        shopping_cart = function(shopping_cart)


def menu():
    # Display the menu
    print(
        "What would you like to do?\n",
        "1. Add an item to your cart.\n",
        "2. Remove an item from your cart.\n",
        "3. View the total cost of your cart.\n",
        "4. Change an item quantity.\n",
        DIVIDER,
        "5. Empty your shopping cart.\n",
        "6. Checkout.\n",
    )
    # Recieve an input of which menu item they want to select
    # Must be a number on the menu
    choice = get_input(
        "",
        options="123456",
    )
    # Return the corresponding function for the menu item (try a switch here)
    match choice:
        case "1":
            return add_item
        case "2":
            return
        case "3":
            return display_cart
        case "4":
            return
        case "5":
            return
        case "6":
            return 
    
    
if __name__ == "__main__":
    main()
