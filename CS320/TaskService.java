/**
 * Title: TaskService.java
 * Purpose: Provides in-memory management of Task objects including creation,
 * deletion, and updates to editable task fields. Ensures all tasks have
 * unique IDs and enforces validation through the Task class rules.
 * Created By: Tyler Hubbell
 * Last Updated: 11/17/2025
 */

import java.util.HashMap;
import java.util.Map;

public class TaskService {

    // In-memory storage for tasks, keyed by unique task ID
    private final Map<String, Task> tasks = new HashMap<>();

    /**
     * Adds a new Task to the service using the provided values.
     * Validates that the task ID is unique before creation.
     *
     * @param taskId      Unique identifier for the task
     * @param name        Name of the task
     * @param description Description of the task
     */

    public void addTask(String taskId, String name, String description) {

        // Ensure the task ID does not already exist
        if (tasks.containsKey(taskId)) {
            throw new IllegalArgumentException("Task ID already exists");
        }

        // Create and store new task
        Task task = new Task(taskId, name, description);
        tasks.put(taskId, task);
    }

    /**
     * Adds an already-instantiated Task object to the service.
     * Useful for flexibility or testing.
     *
     * @param task Task object to add
     */

    public void addTask(Task task) {
        String taskId = task.getTaskId();

        if (tasks.containsKey(taskId)) {
            throw new IllegalArgumentException("Task ID already exists");
        }

        tasks.put(taskId, task);
    }

    /**
     * Deletes a Task from the service by its unique ID.
     *
     * @param taskId ID of the task to remove
     */

    public void deleteTask(String taskId) {

        if (!tasks.containsKey(taskId)) {
            throw new IllegalArgumentException("Task ID not found");
        }

        tasks.remove(taskId);
    }

    /**
     * Updates the name of an existing Task.
     *
     * @param taskId  ID of the task to update
     * @param newName New name to apply (validated by Task class)
     */

    public void updateTaskName(String taskId, String newName) {

        Task task = tasks.get(taskId);

        if (task == null) {
            throw new IllegalArgumentException("Task ID not found");
        }

        task.setName(newName);
    }

    /**
     * Updates the description of an existing Task.
     *
     * @param taskId        ID of the task to update
     * @param newDescription New description to apply (validated by Task class)
     */

    public void updateTaskDescription(String taskId, String newDescription) {

        Task task = tasks.get(taskId);

        if (task == null) {
            throw new IllegalArgumentException("Task ID not found");
        }

        task.setDescription(newDescription);
    }

    /**
     * Retrieves a Task by its ID. Useful for testing and verification.
     *
     * @param taskId ID of the task to retrieve
     * @return Task object or null if not found
     */

    public Task getTask(String taskId) {
        return tasks.get(taskId);
    }
}
