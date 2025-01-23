#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <cmath>

QLineEdit* aCoefficientLineEdit;
QLineEdit* bCoefficientLineEdit;
QLineEdit* cCoefficientLineEdit;

double aCoefficient;
double bCoefficient;
double cCoefficient;

void onCalculateClicked();
bool validateInputData();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget* widget = new QWidget();
    widget->setWindowTitle("Quadratic Slover");
    widget->setMinimumSize(400, 200);
    widget->setWindowIcon(QIcon("QuadraticSlover.png"));

    QLabel* aCoefficientLabel = new QLabel(widget);
    aCoefficientLabel->setText("Enter the coefficient a: ");
    aCoefficientLabel->setMinimumSize(150, 25);

    aCoefficientLineEdit = new QLineEdit(widget);
    aCoefficientLineEdit->setMinimumSize(150, 25);

    QHBoxLayout* aCoefficientLayout = new QHBoxLayout();
    aCoefficientLayout->addWidget(aCoefficientLabel);
    aCoefficientLayout->addWidget(aCoefficientLineEdit);

    QLabel* bCoefficientLabel = new QLabel(widget);
    bCoefficientLabel->setText("Enter the coefficient b: ");
    bCoefficientLabel->setMinimumSize(150, 25);

    bCoefficientLineEdit = new QLineEdit(widget);
    bCoefficientLineEdit->setMinimumSize(150, 25);

    QHBoxLayout* bCoefficientLayout = new QHBoxLayout();
    bCoefficientLayout->addWidget(bCoefficientLabel);
    bCoefficientLayout->addWidget(bCoefficientLineEdit);

    QLabel* cCoefficientLabel = new QLabel(widget);
    cCoefficientLabel->setText("Enter the coefficient c: ");
    cCoefficientLabel->setMinimumSize(150, 25);

    cCoefficientLineEdit = new QLineEdit(widget);
    cCoefficientLineEdit->setMinimumSize(150, 25);

    QHBoxLayout* cCoefficientLayout = new QHBoxLayout();
    cCoefficientLayout->addWidget(cCoefficientLabel);
    cCoefficientLayout->addWidget(cCoefficientLineEdit);

    QPushButton* calculateButton = new QPushButton("Calculate", widget);
    calculateButton->setMinimumSize(150, 25);
    QObject::connect(calculateButton, &QPushButton::clicked, onCalculateClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    widget->setLayout(mainLayout);
    mainLayout->addLayout(aCoefficientLayout);
    mainLayout->addLayout(bCoefficientLayout);
    mainLayout->addLayout(cCoefficientLayout);
    mainLayout->addWidget(calculateButton);

    widget->show();
    return a.exec();
}

void onCalculateClicked() {
    if (validateInputData()) {
        double discriminant = (bCoefficient * bCoefficient) - 4 * aCoefficient * cCoefficient;

        if (discriminant > 0) {
            double root1 = (-bCoefficient + std::sqrt(discriminant)) / (2 * aCoefficient);
            double root2 = (-bCoefficient - std::sqrt(discriminant)) / (2 * aCoefficient);

            QMessageBox messageBox;
            messageBox.setWindowTitle("Answer");
            messageBox.setMinimumSize(150, 50);
            messageBox.setText("The equation has 2 roots: " + QString::number(root1) + ", " + QString::number(root2));
            messageBox.setWindowIcon(QIcon("Answer.png"));
            messageBox.exec();
        } else if (discriminant == 0) {
            double root = -bCoefficient / (2 * aCoefficient);

            QMessageBox messageBox;
            messageBox.setWindowTitle("Answer");
            messageBox.setMinimumSize(150, 50);
            messageBox.setText("The equation has 1 root: " + QString::number(root));
            messageBox.setWindowIcon(QIcon("Answer.png"));
            messageBox.exec();
        } else {
            QMessageBox messageBox;
            messageBox.setWindowTitle("Answer");
            messageBox.setMinimumSize(150, 50);
            messageBox.setText("The equation has no real roots");
            messageBox.setWindowIcon(QIcon("Answer.png"));
            messageBox.exec();
        }
    }
}

bool validateInputData() {
    bool aOK;
    bool bOK;
    bool cOK;

    aCoefficient = aCoefficientLineEdit->text().toDouble(&aOK);
    bCoefficient = bCoefficientLineEdit->text().toDouble(&bOK);
    cCoefficient = cCoefficientLineEdit->text().toDouble(&cOK);

    if (!aOK || !bOK || !cOK) {
        QMessageBox::warning(nullptr, "Error", "Please enter the correct numerical values for all coefficients");
        return false;
    }

    if (aCoefficient == 0) {
        QMessageBox::warning(nullptr, "Error", "The coefficient 'a' cannot be zero");
        return false;
    }

    return true;
}
