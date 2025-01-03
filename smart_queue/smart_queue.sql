-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: Lug 02, 2023 alle 10:29
-- Versione del server: 10.4.27-MariaDB
-- Versione PHP: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `smart_queue`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `tab_admin`
--

CREATE TABLE `tab_admin` (
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `tab_admin`
--

INSERT INTO `tab_admin` (`email`, `password`) VALUES
('schettinifrancesco@gmail.com', 'schettini'),
('turcofrancesco@gmail.com', 'turco');

-- --------------------------------------------------------

--
-- Struttura della tabella `tab_allarme`
--

CREATE TABLE `tab_allarme` (
  `id_allarme` int(11) NOT NULL,
  `data_ora_fine_allarme` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `durata` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `tab_allarme`
--

INSERT INTO `tab_allarme` (`id_allarme`, `data_ora_fine_allarme`, `durata`) VALUES
(1, '2023-06-25 13:56:56', '00:00:15'),
(8, '2023-06-27 17:14:02', '00:00:10'),
(9, '2023-07-01 15:58:10', '00:00:01');

-- --------------------------------------------------------

--
-- Struttura della tabella `tab_entrate`
--

CREATE TABLE `tab_entrate` (
  `fascia_oraria` int(255) NOT NULL,
  `numero_visitatori` int(11) NOT NULL,
  `ID` int(11) NOT NULL,
  `Data` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `tab_entrate`
--

INSERT INTO `tab_entrate` (`fascia_oraria`, `numero_visitatori`, `ID`, `Data`) VALUES
(9, 10, 1, '2023-06-30'),
(10, 11, 2, '2023-06-30'),
(11, 2, 3, '2023-06-30'),
(12, 0, 4, '2023-06-30'),
(13, 2, 5, '2023-06-30'),
(14, 5, 7, '2023-06-30'),
(15, 0, 8, '2023-06-30'),
(16, 12, 9, '2023-06-30'),
(17, 3, 10, '2023-06-30'),
(9, 2, 12, '2023-07-01'),
(10, 2, 14, '2023-07-01'),
(9, 5, 15, '2023-07-14'),
(10, 3, 16, '2023-07-14'),
(15, 7, 23, '2023-07-01'),
(9, 6, 24, '2023-07-02');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `tab_admin`
--
ALTER TABLE `tab_admin`
  ADD PRIMARY KEY (`email`);

--
-- Indici per le tabelle `tab_allarme`
--
ALTER TABLE `tab_allarme`
  ADD PRIMARY KEY (`id_allarme`);

--
-- Indici per le tabelle `tab_entrate`
--
ALTER TABLE `tab_entrate`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `tab_allarme`
--
ALTER TABLE `tab_allarme`
  MODIFY `id_allarme` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT per la tabella `tab_entrate`
--
ALTER TABLE `tab_entrate`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
