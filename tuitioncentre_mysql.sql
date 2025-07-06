-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 22, 2024 at 03:23 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `tuitioncentre`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `AdminID` varchar(6) NOT NULL,
  `AdminPass` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`AdminID`, `AdminPass`) VALUES
('A12345', 'Arshad');

-- --------------------------------------------------------

--
-- Table structure for table `enrollment`
--

CREATE TABLE `enrollment` (
  `StudentID` varchar(12) NOT NULL,
  `SubjectID` varchar(4) NOT NULL,
  `Feedback` varchar(50) DEFAULT 'N/A',
  `Status` varchar(6) DEFAULT 'UNPAID',
  `FeesPeriod` date DEFAULT (curdate() + interval 1 month)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `enrollment`
--

INSERT INTO `enrollment` (`StudentID`, `SubjectID`, `Feedback`, `Status`, `FeesPeriod`) VALUES
('071220140000', 'SB04', 'Tutor is awesome', 'PAID', '2024-02-18'),
('071220140000', 'SB08', 'N/A', 'PAID', '2024-02-18'),
('071220140000', 'SB10', 'N/A', 'PAID', '2024-02-18'),
('071220140000', 'SB12', 'N/A', 'PAID', '2024-02-18'),
('071220140000', 'SB14', 'N/A', 'PAID', '2024-02-18'),
('071220140751', 'SB08', 'N/A', 'UNPAID', '2024-02-18'),
('071220140752', 'SB08', 'Easy to understand', 'UNPAID', '2024-02-18'),
('081220140751', 'SB07', 'Tutor is very friendly', 'UNPAID', '2024-02-18'),
('081220140752', 'SB07', 'Awesome', 'UNPAID', '2024-02-18'),
('081220140753', 'SB07', 'Good!', 'UNPAID', '2024-02-18'),
('081220140759', 'SB70', 'Good.', 'UNPAID', '2024-02-18');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `PaymentID` int(11) NOT NULL,
  `StudentID` varchar(12) NOT NULL,
  `Total_Subject` int(11) NOT NULL DEFAULT 0,
  `Total_Fees` decimal(10,2) NOT NULL DEFAULT 0.00,
  `Payment_Date` date NOT NULL DEFAULT curdate(),
  `AdminID` varchar(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`PaymentID`, `StudentID`, `Total_Subject`, `Total_Fees`, `Payment_Date`, `AdminID`) VALUES
(1004, '071220140000', 1, 20.00, '2024-01-18', 'A12345'),
(1005, '071220140000', 6, 120.00, '2024-01-18', 'A12345');

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `StudentID` varchar(12) NOT NULL,
  `StudentPass` varchar(20) NOT NULL,
  `Name` varchar(50) NOT NULL,
  `Age` int(11) NOT NULL,
  `Phone_Number` varchar(10) NOT NULL,
  `AdminID` varchar(6) NOT NULL,
  `AccountStatus` varchar(12) DEFAULT 'ACTIVE'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`StudentID`, `StudentPass`, `Name`, `Age`, `Phone_Number`, `AdminID`, `AccountStatus`) VALUES
('071220140000', 'arshad', 'Muhd Arshad Bin Mohd Din', 17, '0197970789', 'A12345', 'ACTIVE'),
('071220140751', 'arshad', 'Muhammad Haziq Bin Abu', 17, '0145678901', 'A12345', 'ACTIVE'),
('071220140752', 'arshad2', 'Muhammad Abu Bin Ali', 17, '0167890123', 'A12345', 'ACTIVE'),
('071220140753', 'arshad', 'Muhammad Arshad Bin Mohamad Din', 17, '0189012345', 'A12345', 'ACTIVE'),
('071220140755', 'studentpass10', 'Sophia Tan Xie', 17, '0101234567', 'A12345', 'ACTIVE'),
('071220140756', 'meow', 'Pavithran Muniandi', 17, '0123456789', 'A12345', 'ACTIVE'),
('081220140751', 'arshad', 'Kamarul Jamal Abdul Samad', 16, '0198695032', 'A12345', 'ACTIVE'),
('081220140752', 'arshad', 'Fikri Zainuddin', 16, '0197970753', 'A12345', 'ACTIVE'),
('081220140753', 'studentpass1', 'Muhammad Adib Zakwan', 16, '0112345678', 'A12345', 'ACTIVE'),
('081220140754', 'studentpass5', 'Siti Sarah Zulaika', 16, '0156789012', 'A12345', 'ACTIVE'),
('081220140755', 'studentpass7', 'Hana Humaira Binti Onn', 16, '0178901234', 'A12345', 'ACTIVE'),
('081220140756', 'studentpass9', 'Emanuel Lim Hong', 16, '0190123456', 'A12345', 'ACTIVE'),
('081220140759', 'arshad', 'Muhd Arshad Din', 16, '0197970788', 'A12345', 'ACTIVE');

-- --------------------------------------------------------

--
-- Table structure for table `subject`
--

CREATE TABLE `subject` (
  `SubjectID` varchar(4) NOT NULL,
  `Name` varchar(30) NOT NULL,
  `Fees` decimal(4,2) NOT NULL,
  `Quota` int(11) DEFAULT 15,
  `Category_Age` int(11) NOT NULL,
  `AdminID` varchar(6) NOT NULL,
  `TutorID` varchar(12) DEFAULT 'NONE'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `subject`
--

INSERT INTO `subject` (`SubjectID`, `Name`, `Fees`, `Quota`, `Category_Age`, `AdminID`, `TutorID`) VALUES
('SB01', 'MATHEMATICS', 20.00, 4, 16, 'A12345', '993456719012'),
('SB02', 'MATHEMATICS', 20.00, 15, 17, 'A12345', '993456719012'),
('SB03', 'PHYSICS', 20.00, 15, 16, 'A12345', '987354321012'),
('SB04', 'PHYSICS', 20.00, 14, 17, 'A12345', '987354321012'),
('SB07', 'ADDITIONAL MATHEMATICS', 20.00, 5, 16, 'A12345', '994556677889'),
('SB08', 'ADDITIONAL MATHEMATICS', 20.00, 10, 17, 'A12345', '994556677889'),
('SB09', 'DATABASE', 20.00, 7, 16, 'A12345', '982233445466'),
('SB10', 'DATABASE', 20.00, 8, 17, 'A12345', '982233445466'),
('SB11', 'BAHASA MELAYU', 20.00, 14, 16, 'A12345', '987788990011'),
('SB12', 'BAHASA MELAYU', 20.00, 15, 17, 'A12345', '987788990011'),
('SB13', 'BAHASA INGGERIS', 20.00, 14, 16, 'A12345', '013344556677'),
('SB14', 'BAHASA INGGERIS', 20.00, 15, 17, 'A12345', '013344556677'),
('SB15', 'BAHASA CINA', 20.00, 0, 16, 'A12345', '999900112233'),
('SB16', 'BAHASA CINA', 20.00, 15, 17, 'A12345', '999900112233'),
('SB17', 'EKONOMI', 20.00, 15, 16, 'A12345', '986677889900'),
('SB18', 'EKONOMI', 20.00, 15, 17, 'A12345', '986677889900'),
('SB19', 'PENDIDIKAN SENI VISUAL', 20.00, 1, 16, 'A12345', '998877665544'),
('SB20', 'PENDIDIKAN SENI VISUAL', 20.00, 15, 17, 'A12345', '998877665544'),
('SB70', 'BIOLOGY', 30.00, 1, 16, 'A12345', '981220140752'),
('SB71', 'BIOLOGY', 30.00, 0, 17, 'A12345', '981220140752'),
('SB89', 'SCIENCE COMPUTER', 20.00, 0, 16, 'A12345', '991220140753'),
('SB98', 'AKAUN', 30.00, 0, 16, 'A12345', '001220140753'),
('SB99', 'AKAUN', 30.00, 0, 17, 'A12345', '001220140753');

-- --------------------------------------------------------

--
-- Table structure for table `tutor`
--

CREATE TABLE `tutor` (
  `TutorID` varchar(12) NOT NULL,
  `AdminID` varchar(6) NOT NULL,
  `TutorPass` varchar(20) NOT NULL,
  `Name` varchar(50) NOT NULL,
  `Phone_Number` varchar(10) NOT NULL,
  `Subject_Experties` varchar(30) NOT NULL,
  `Available_Tutoring_Date` date NOT NULL,
  `AccountStatus` varchar(12) DEFAULT 'ACTIVE'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tutor`
--

INSERT INTO `tutor` (`TutorID`, `AdminID`, `TutorPass`, `Name`, `Phone_Number`, `Subject_Experties`, `Available_Tutoring_Date`, `AccountStatus`) VALUES
('001220140753', 'A12345', 'meow', 'Muhd Arshad', '0192220123', 'AKAUN', '2024-12-12', 'ACTIVE'),
('013344556677', 'A12345', 'password7', 'David Lim', '0198901234', 'BAHASA INGGERIS', '2023-07-09', 'ACTIVE'),
('981220140752', 'A12345', 'Arshad', 'Muhd Arshad Din Dahlan', '0192920834', 'BIOLOGY', '2024-01-18', 'ACTIVE'),
('982233445466', 'A12345', 'password10', 'Sophia Tan', '0141234567', 'DATABASE', '2023-10-08', 'ACTIVE'),
('986677889900', 'A12345', 'password9', 'Samuel Ng', '0110123456', 'EKONOMI', '2023-09-30', 'ACTIVE'),
('987354321012', 'A12345', 'password2', 'Jane Smith', '0162345678', 'PHYSICS', '2024-01-20', 'ACTIVE'),
('987788990011', 'A12345', 'password6', 'Eva Wong', '0187890123', 'BAHASA MELAYU', '2023-06-18', 'ACTIVE'),
('991220140753', 'A12345', 'ARSHAD', 'MUHAMMAD ARSHAD DIN', '0198983012', 'SCIENCE COMPUTER', '2024-12-03', 'ACTIVE'),
('993456719012', 'A12345', 'password1', 'John Doe', '0122456789', 'MATHEMATICS', '2023-01-15', 'ACTIVE'),
('994556677889', 'A12345', 'password4', 'Alice Lee', '0115679801', 'ADDITIONAL MATHEMATICS', '2024-01-01', 'ACTIVE'),
('998877665544', 'A12345', 'password5', 'Charlie Tan', '0176789012', 'PENDIDIKAN SENI VISUAL', '2023-05-22', 'ACTIVE'),
('999900112233', 'A12345', 'password8', 'Grace Chen', '0129012345', 'BAHASA CINA', '2023-08-14', 'ACTIVE');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`AdminID`);

--
-- Indexes for table `enrollment`
--
ALTER TABLE `enrollment`
  ADD PRIMARY KEY (`StudentID`,`SubjectID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`PaymentID`),
  ADD KEY `StudentID` (`StudentID`),
  ADD KEY `AdminID` (`AdminID`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`StudentID`),
  ADD UNIQUE KEY `Phone_Number` (`Phone_Number`),
  ADD KEY `AdminID` (`AdminID`);

--
-- Indexes for table `subject`
--
ALTER TABLE `subject`
  ADD PRIMARY KEY (`SubjectID`),
  ADD KEY `AdminID` (`AdminID`),
  ADD KEY `TutorID` (`TutorID`);

--
-- Indexes for table `tutor`
--
ALTER TABLE `tutor`
  ADD PRIMARY KEY (`TutorID`),
  ADD UNIQUE KEY `Phone_Number` (`Phone_Number`),
  ADD KEY `AdminID` (`AdminID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `PaymentID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1006;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `payment_ibfk_1` FOREIGN KEY (`StudentID`) REFERENCES `student` (`StudentID`),
  ADD CONSTRAINT `payment_ibfk_2` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`);

--
-- Constraints for table `student`
--
ALTER TABLE `student`
  ADD CONSTRAINT `student_ibfk_1` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`);

--
-- Constraints for table `subject`
--
ALTER TABLE `subject`
  ADD CONSTRAINT `subject_ibfk_1` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`),
  ADD CONSTRAINT `subject_ibfk_2` FOREIGN KEY (`TutorID`) REFERENCES `tutor` (`TutorID`);

--
-- Constraints for table `tutor`
--
ALTER TABLE `tutor`
  ADD CONSTRAINT `tutor_ibfk_1` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
