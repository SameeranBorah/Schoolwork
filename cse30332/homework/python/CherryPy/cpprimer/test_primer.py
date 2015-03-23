import unittest
import requests
import json

class TestCherrypyPrimer(unittest.TestCase):

	#@classmethod
	#def setUpClass(self):
	SITE_URL = 'http://127.0.0.1:40041'  # CHANGE THIS TO YOUR PERSONAL PORT NUMBER
	DICT_URL = SITE_URL + '/dictionary/'

	def reset_data(self):
		r = requests.delete(self.DICT_URL)

	def is_json(self, resp):
		try:
			json.loads(resp)
			return True
		except ValueError:
			return False

	def test_dict_get(self):
		self.reset_data()
		key = 'a4'
		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'error')

	def test_dict_put(self):
		self.reset_data()
		key = 'a4'

		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['value'], m['value'])

	def test_dict_delete(self):
		self.reset_data()
		key = 'a4'

		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.delete(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'error')

	def test_dict_index_get(self):
		self.reset_data()

		key = 'a4'
		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		entries = resp['entries']
		mkv = entries[0]
		self.assertEquals(mkv['key'], key)
		self.assertEquals(mkv['value'], m['value'])

	def test_dict_index_post(self):
		self.reset_data()

		m = {}
		m['key'] = 'a4'
		m['value'] = '1995'

		r = requests.post(self.DICT_URL, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		entries = resp['entries']
		mkv = entries[0]
		self.assertEquals(mkv['key'], m['key'])
		self.assertEquals(mkv['value'], m['value'])

if __name__ == "__main__":
	unittest.main()

