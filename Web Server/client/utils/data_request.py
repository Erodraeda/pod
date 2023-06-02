import requests
from utils.debug_terminal import debugTerminal

class DataRequest:
    def __init__(self):
      self.api_url = 'http://localhost:8080'

    def get(self, arg1):
        try:
            if arg1 == 'all':
                response = requests.get(f'{self.api_url}/')
            else:
                response = requests.get(f'{self.api_url}/get/{arg1}')    
            
            response_json = response.json()

            debugTerminal(f'response: {response}', 'success')
            debugTerminal(f'response: {response_json}', 'info')
        except Exception as err:
            debugTerminal(f'{err}', 'error')
        
    def add(self, arg1):
        try:
            response = requests.post(f'{self.api_url}/add/{arg1}')
            response_json = response.json()

            debugTerminal(f'response: {response}', 'success')
            debugTerminal(f'response: {response_json}', 'info')
        except Exception as err:
            debugTerminal(f'{err}', 'error')
    
    def delete(self, arg1):
        try:
            response = requests.post(f'{self.api_url}/delete/{arg1}')    
            response_json = response.json()

            debugTerminal(f'response: {response}', 'success')
            debugTerminal(f'response: {response_json}', 'info')
        except Exception as err:
            debugTerminal(f'{err}', 'error')

    def update(self, arg1, arg2):
        try:
            response = requests.post(f'{self.api_url}/update/{arg1}/{arg2}')    
            response_json = response.json()

            debugTerminal(f'response: {response}', 'success')
            debugTerminal(f'response: {response_json}', 'info')
        except Exception as err:
            debugTerminal(f'{err}', 'error')