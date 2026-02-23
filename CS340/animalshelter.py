"""
Title: animalshelter.py
Course: CS 340 - Client/Server Development
Project: Project One (CRUD Module)
Author: Tyler Hubbell

Purpose:
Provide a reusable Python module that implements full CRUD (Create, Read,
Update, Delete) functionality for the animals collection stored in MongoDB.

Notes:
- Read uses find() (not find_one()) per rubric requirement
- Update/Delete return counts per rubric requirement
"""

from pymongo import MongoClient
from pymongo.errors import PyMongoError


class AnimalShelter(object):
    """CRUD operations for the animals collection in MongoDB."""

    def __init__(self, username="aacuser", password="12345678"):
        HOST = "localhost"
        PORT = 27017
        DB = "aac"
        COL = "animals"

        # IMPORTANT:
        # In the Codio environment for CS-340, the aacuser account is commonly
        # authenticated against the 'aac' database (not 'admin').
        AUTH_DB = "aac"

        try:
            self.client = MongoClient(
                f"mongodb://{username}:{password}@{HOST}:{PORT}/{DB}?authSource={AUTH_DB}"
            )
            self.database = self.client[DB]
            self.collection = self.database[COL]
        except PyMongoError as e:
            print(f"[Connection Error] {e}")

    def create(self, data):
        if data is None or not isinstance(data, dict):
            return False

        try:
            result = self.collection.insert_one(data)
            return bool(result.acknowledged)
        except PyMongoError as e:
            print(f"[Create Error] {e}")
            return False

    def read(self, query):
        if query is None:
            query = {}

        if not isinstance(query, dict):
            return []

        try:
            cursor = self.collection.find(query)
            return list(cursor)
        except PyMongoError as e:
            print(f"[Read Error] {e}")
            return []

    def update(self, query, new_values):
        if query is None or not isinstance(query, dict):
            return 0
        if new_values is None or not isinstance(new_values, dict) or len(new_values) == 0:
            return 0

        try:
            result = self.collection.update_many(query, {"$set": new_values})
            return int(result.modified_count)
        except PyMongoError as e:
            print(f"[Update Error] {e}")
            return 0

    def delete(self, query):
        if query is None or not isinstance(query, dict) or len(query) == 0:
            return 0

        try:
            result = self.collection.delete_many(query)
            return int(result.deleted_count)
        except PyMongoError as e:
            print(f"[Delete Error] {e}")
            return 0
