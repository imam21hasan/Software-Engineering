import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class StudentTest {

    private Student student;

    @BeforeEach
    void setUp() {
        student = new Student("Hasan", 80);
    }

    // ==========================================
    // assertEquals()
    // ==========================================

    @Test
    void testGetNameValid() {
        assertEquals("Hasan", student.getName());
    }

    @Test
    void testGetMarksValid() {
        assertEquals(80, student.getMarks());
    }

    // ==========================================
    // assertTrue()
    // ==========================================

    @Test
    void testIsPassedTrue() {

        assertTrue(student.isPassed());

    }

    // ==========================================
    // assertFalse()
    // ==========================================

    @Test
    void testIsPassedFalse() {

        Student s = new Student("Karim", 20);

        assertFalse(s.isPassed());

    }

    // ==========================================
    // assertNull()
    // ==========================================

    @Test
    void testFindStudentInvalid() {

        Student s = student.findStudent("Rahim");

        assertNull(s);

    }

    // ==========================================
    // assertNotNull()
    // ==========================================

    @Test
    void testFindStudentValid() {

        Student s = student.findStudent("Hasan");

        assertNotNull(s);

    }

    // ==========================================
    // assertThrows()
    // ==========================================

    @Test
    void testConstructorInvalidName() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> new Student("", 80)
        );

        assertEquals("Name cannot be empty",
                exception.getMessage());

    }

    @Test
    void testConstructorInvalidMarks() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> new Student("Hasan", 120)
        );

        assertEquals("Marks must be between 0 and 100",
                exception.getMessage());

    }

}