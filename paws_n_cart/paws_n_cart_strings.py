""" Shopping Cart String Challenge """

ITEM_SEPARATOR = '~'
INFO_SEPARATOR = "+"
DIVIDER = "*" * 50 + "\n"


def display_cart(shopping_cart):
    formatted_cart = shopping_cart.replace(ITEM_SEPARATOR, "\n- ")
    print(f"Your Cart:{formatted_cart}")

def main():
    """The main function controls the flow of the program.
    Welcome to Paws n Cart, the string challenge shopping cart program.

    Since this is a string challenge, this program will be
    avoiding lists and classes as much as possible.
    """
    fancy_title()
    menu()
    price_catalog = ""
    shopping_cart = ""
    for item in ["cat", "dog", "turtle"]:
        shopping_cart += ITEM_SEPARATOR + item
    
    display_cart(shopping_cart)
    
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
    
    # Return the corresponding function for the menu item (try a switch here)
    match 5:
        case 1:
            return
        case 2:
            return
        case 3:
            return
        case 4:
            return
    return True

def fancy_title():
    print("title art here")
    
    
if __name__ == "__main__":
    main()