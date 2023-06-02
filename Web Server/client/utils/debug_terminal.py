from datetime import datetime

# Control (enable / disable) terminal messages
debug_status = True

def debugTerminal(message, type, debug=debug_status):
    if debug == True:
        # Format the message and print it to the terminal
        print_message = formatMessage(message, type)
        print(print_message)

def formatMessage(message, type):
    # Get the current datetime
    current_datetime = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    # Set the icon, message title, and color code based on the message type
    icon = ''
    message_title = ''
    color_code = ''
    reset_color_code = '\033[0m'

    if type == 'warning':
        icon = '⛔'
        message_title = 'ALERT'
        color_code = '\033[93m'  # Yellow

    elif type == 'error':
        icon = '❌'
        message_title = 'ERROR'
        color_code = '\033[91m'  # Red

    elif type == 'success':
        icon = '✅'
        message_title = 'SUCCESS'
        color_code = '\033[92m'  # Green

    else:
        icon = '📌'
        message_title = 'INFO'
        color_code = '\033[94m'  # Blue

    # Create the final formatted message
    final_message = f'{icon} [ {current_datetime} ] {message_title}: {color_code}{message}{reset_color_code}'

    return final_message