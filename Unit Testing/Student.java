public class Student {

    private String name;
    private int marks;

    public Student(String name, int marks) {

        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Name cannot be empty");
        }

        if (marks < 0 || marks > 100) {
            throw new IllegalArgumentException("Marks must be between 0 and 100");
        }

        this.name = name;
        this.marks = marks;
    }

    public String getName() {
        return name;
    }

    public int getMarks() {
        return marks;
    }

    public boolean isPassed() {
        return marks >= 40;
    }

    public Student findStudent(String name) {

        if (name.equals(this.name))
            return this;

        return null;
    }
}